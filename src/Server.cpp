#include "../include/Server.hpp"

Server::Server(std::string host, std::string port, std::string password)
	: _name("irc.local"), _host(host), _port(port), _password(password), _message(new Message()), reply(new Reply(this)), ch_limit(20)
{
	init();
}

Server::~Server()
{
	delete _message;
	delete reply;
	for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		delete *it;
	}
	for (std::list<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		delete *it;
	}
	for (std::vector<pollfd>::iterator it = _poll_fd_vec.begin(); it != _poll_fd_vec.end(); it++)
	{
		close(it->fd);
	}
}

void Server::init()
{
	int on = 1;
	addrinfo hints;
	addrinfo *res;
	int socket_fd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &res) != 0)
	{
		throw std::runtime_error("error: could not get address info");
	}

	if ((socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
	{
		throw std::runtime_error("error: could not get socket_fd");
	}

	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)
	{
		freeaddrinfo(res);
		close(socket_fd);
		throw std::runtime_error("error: could not set socket options");
	}

	if (setsockopt(socket_fd, SOL_SOCKET, SO_NOSIGPIPE, (char *)&on, sizeof(on)) == -1)
	{
		freeaddrinfo(res);
		close(socket_fd);
		throw std::runtime_error("error: could not set socket options");
	}

	if (bind(socket_fd, res->ai_addr, res->ai_addrlen) != 0)
	{
		freeaddrinfo(res);
		close(socket_fd);
		throw std::runtime_error("error: could not bind");
	}

	if (listen(socket_fd, 32) == -1)
	{
		freeaddrinfo(res);
		close(socket_fd);
		throw std::runtime_error("error: could not listen");
	}
	freeaddrinfo(res);
	_socket_fd = socket_fd;
	_cmd = NULL;
}

void Server::server_run()
{
	// poll 초기화
	pollfd tmp_poll_fd = {_socket_fd, POLLIN, 0};
	pollfd cur_poll_fd;

	// 논블록킹으로 초기화
	if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("error: could not fcntl");
	}
	// poll 디스크립터 벡터에 저장
	_poll_fd_vec.push_back(tmp_poll_fd);
	std::vector<pollfd>::iterator it_poll_fd;
	std::cout << "Server: " << _host << ":" << _port << std::endl;

	// 서버 실행
	while (42)
	{
		it_poll_fd = _poll_fd_vec.begin();
		if (poll(&(*it_poll_fd), _poll_fd_vec.size(), 5000) == -1)
		{
			throw std::runtime_error("error: could not poll");
		}
		// pollFd 에서 이벤트 발생 조회
		for (std::vector<pollfd>::iterator it = _poll_fd_vec.begin(); it != _poll_fd_vec.end(); it++)
		{
			cur_poll_fd = *it;
			// 소켓 연결이 끊겼을 경우
			if ((cur_poll_fd.revents & POLLHUP) == POLLHUP)
			{
				std::cout << "Connection lost" << std::endl << std::flush;
				delete_client(cur_poll_fd.fd);
				break;
			}
			// tmp_poll_fd 돌면서 이벤트가 POLLIN 이면 해당 명령 실행 
			else if ((cur_poll_fd.revents & POLLIN) == POLLIN)
			{
				// 클라이언트인 유저 추가
				if (cur_poll_fd.fd == _socket_fd)
				{
					accept_client();
				}
				// 이벤트 발생한 유저 메시지 확인
				else
				{
					recv_message(cur_poll_fd.fd);
				}
				break;
			}
		}
	}
}

int Server::recv_message(int cur_fd)
{
	Client* 	client = get_client_by_socket_fd(cur_fd);
	char 		buf = '\n';
	int 		b = 0;
	int 		nbytes;
	Tcpflow     flow;

	while (42)
	{
		nbytes = recv(cur_fd, &buf, 1, 0);
		if (nbytes < 0)
			continue;
		client->add_buffer(buf);
		if (b > 500)
			client->add_buffer("/QUIT you can't use this server\r\n");
		if (client->get_buffer().find("\n") != std::string::npos)
		{
			try
			{
				flow.to_server(client, client->get_buffer());
				_cmd = _message->parse_msg(client->get_buffer());
				_cmd->execute_command(this, client);
				if (_cmd->name == "QUIT")
					client = NULL;
			}
			catch (const Irc_exception& e)
			{
				flow.to_client(client, e.message);
				serverResponse(":" + get_name() + " " + e.number + " " + client->get_nickname() + " " + e.message, cur_fd);
				if (_cmd)
					_cmd->init_cmd();
			}
			catch (const Connection_error& e)
			{
				serverResponse(e.message, cur_fd);
				delete_client(client->get_socket_fd());
				client = NULL;
			}
			catch (const Unknown_error& e)
			{
			}
			if (client)
				client->clear_buffer();
			break;
		}
		else
			break;
		b++;
	}
	return 0;
}

int Server::accept_client()
{
	int         client_fd;
	sockaddr_in client_addr;
	socklen_t   s_size;

	// 클라이언트 fd 받기
	s_size = sizeof(client_addr);
	if ((client_fd = accept(_socket_fd, (sockaddr *)&client_addr, &s_size)) == -1)
	{
		throw std::runtime_error("error: could not accept client");
	}

	// 새로운 클라이언트 fd, poll 벡터에 저장
	pollfd new_poll_fd_vec = {client_fd, POLLIN, 0};
	_poll_fd_vec.push_back(new_poll_fd_vec);
	
	// 논블록킹 모드
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		throw std::runtime_error("error: could not fcntl");
	}

	// 새로운 fd 받아 클라이언트 만들기
	Client *new_client = new Client(client_fd);
	_clients.push_back(new_client);
	std::cout << "New client: " << new_client->get_socket_fd() << std::endl;
	return client_fd;
}

std::string Server::get_password()
{
	return _password;
}

std::string Server::get_host()
{
    return _host;
}

std::string Server::get_name()
{
	return _name;
}

std::list<Client *> Server::get_clients()
{
	return _clients;
}


void Server::message_all(std::string message)
{
	Tcpflow     flow;

    if (message.find("\r\n"))
		message += "\r\n";
	for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
        std::cout << (*it)->get_socket_fd() << std::endl;
		flow.to_client(*it, message);
		if (send((*it)->get_socket_fd(), message.c_str(), strlen(message.c_str()), 0) == -1)
			throw std::runtime_error("Couldn't SEND message_all");
	}
}

void Server::delete_client(int socket_fd)
{
	Client*	client = get_client_by_socket_fd(socket_fd);

	for (std::list<Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (leave_channel(client, *it))
			it = _channels.begin();
	}
	for (std::vector<pollfd>::iterator it = _poll_fd_vec.begin(); it != _poll_fd_vec.end(); ++it)
	{
		if ((*it).fd == socket_fd)
		{
			close(socket_fd);
			_poll_fd_vec.erase(it);
			break;
		}
	}
	for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if ((*it)->get_socket_fd() == socket_fd)
		{
			delete *it;
			_clients.erase(it);
			break;
		}
	}
}

bool Server::leave_channel(Client* client, Channel* ch)
{
	ch->leave(client);
	client->delete_channel(ch);
	if (ch->joined->size() == 0)
	{
		delete_channel(ch);
		return (true);
	}
	return (false);
}

void Server::delete_channel(Channel* ch)
{
	_channels.remove(ch);
	delete ch;
}

Client* Server::get_client_by_socket_fd(int socket_fd)
{
	std::list<Client *>::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		if ((*it)->get_socket_fd() == socket_fd)
			return (*it);
		it++;
	}
	return (NULL);
}

Client* Server::get_client_by_nickname(std::string nickname)
{
	std::list<Client *>::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		if ((*it)->get_nickname() == nickname)
			return (*it);
		it++;
	}
	return (NULL);
}

/** 채널 관련 함수 **/
Channel* Server::add_channel(std::string name, Client* client)
{
	Channel*	new_channel = new Channel(name);

	new_channel->joined->add(client);
	new_channel->op->add(client);
	this->_channels.push_back(new_channel);
	client->add_channel(new_channel);
	return (new_channel);
}

std::list<Channel *>  Server::get_channel_list()
{
	return _channels;
}

Channel* Server::get_channel(std::string name)
{
	std::list<Channel *>::iterator		ch_iter = _channels.begin();
	std::list<Channel *>::iterator		ch_end = _channels.end();

	for (; ch_iter!=ch_end; ch_iter++)
	{
		if ((*ch_iter)->get_name() == name)
			return *ch_iter;
	}

	return NULL;
}

void Server::serverResponse(std::string message, int client_fd)
{
	std::string res;

	res += message + "\r\n";
	if (send(client_fd, res.c_str(), strlen(res.c_str()), 0) == -1)
		throw std::runtime_error("Couldn't SEND socket");
}
