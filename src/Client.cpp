#include "../include/Client.hpp"

Client::Client(int client_fd)
{
	struct sockaddr_in clientaddr;
	socklen_t client_len;
	
	client_len = sizeof(clientaddr);
	this->_client_fd = client_fd;
	getsockname(client_sockfd, (struct sockaddr *)&clientaddr, &client_len);
	this->_hostname = inet_ntoa(clientaddr.sin_addr);
	this->_nickname = "";
	this->_auth = false;
};

Client::~Client()
{
	this->_mode.clear();
	this->_mode['i'] = false;
	this->_mode['o'] = false;
	this->_mode['s'] = false;
	this->_mode['w'] = false;
}

void Client::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
}

int Client::get_socket_fd()
{
	return (this->_client_fd);
}

std::string Client::get_nickname()
{
	return (this->_nickname);
}

void Client::set_username(std::string username)
{
	_username = username;
}

std::string Client::get_username()
{
	return (this->_username);
}

void Client::set_realname(std::string realname)
{
	_realname = realname;
}

std::string Client::get_realname()
{
	return (this->_realname);
}

std::string Client::get_hostname()
{
	return (this->_hostname);
}

std::string Client::get_message_prefix()
{
	std::string prefix;
	prefix += _nickname;
	prefix += "!";
	prefix += _username;
	prefix += "@";
	prefix += _hostname;
	return (prefix);
}

bool Client::is_auth()
{
	return (this->_auth);
}

void Client::set_auth()
{
	this->_auth = true;
}

void Client::add_channel(Channel *channel)
{
	std::list<Channel *>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if ((*it)->get_name() == channel->get_name())
			return;
	}
	_channels.push_back(channel);
}

void Client::delete_channel(Channel *channel)
{
	std::list<Channel *>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if ((*it) == channel)
		{
			_channels.erase(it);
			return;
		}
	}
}

void Client::message_client(std::string message)
{
	if (message.find("\r\n"))
		message += "\r\n";
	if (send(this->get_socket_fd(), message.c_str(), strlen(message.c_str()), 0) == -1)
		throw std::runtime_error("Could't send messageUser");
}

void Client::set_flag(char c, bool is_on)
{
	if (this->_mode.find(c) != this->_mode.end())
		this->_mode[c] = is_on;
}

