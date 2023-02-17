#include "../include/Client.hpp"

Client::Client(int client_fd)
{
	sockaddr_in clientaddr;
	socklen_t client_len;
	
	client_len = sizeof(clientaddr);
	this->_client_fd = client_fd;
	getsockname(_client_fd, (struct sockaddr *)&clientaddr, &client_len);
	this->_hostname = inet_ntoa(clientaddr.sin_addr);
	this->_nickname = "";
	this->_auth = false;
};

Client::Client(const Client &origin)
{
	this->_nickname = origin._nickname;
	this->_username = origin._username;
	this->_realname = origin._realname;
	this->_hostname = origin._hostname;
	this->_auth = origin._auth;
	this->_channels = origin._channels;
	this->_mode = origin._mode;
	this->_client_fd = origin._client_fd;
}

Client::~Client()
{
	this->_mode.clear();
	this->_mode['i'] = false;
	this->_mode['o'] = false;
	this->_mode['s'] = false;
	this->_mode['w'] = false;
}

int Client::get_socket_fd()
{
	return (this->_client_fd);
}

std::string Client::get_nickname()
{
	if (this->_nickname.size() == 0)
		return ("*");
	return (this->_nickname);
}

void Client::set_nickname(std::string nickname)
{
	this->_nickname = nickname;
}

std::string Client::get_username()
{
	if (this->_username.size() == 0)
		return ("*");
	return (this->_username);
}

void Client::set_username(std::string username)
{
	_username = username;
}

std::string Client::get_hostname()
{
	if (this->_hostname.size() == 0)
		return ("*");
	return (this->_hostname);
}

void Client::set_hostname(std::string hostname)
{
	_hostname = hostname;
}

std::string Client::get_servername()
{
	if (this->_servername.size() == 0)
		return ("*");
	return (this->_servername);
}

void Client::set_servername(std::string servername)
{
	_servername = servername;
}

std::string Client::get_realname()
{
	if (this->_realname.size() == 0)
		return ("*");
	return (this->_realname);
}

void Client::set_realname(std::string realname)
{
	_realname = realname;
}

std::string Client::get_message_prefix()
{
	std::string prefix;
	prefix += get_nickname();
	prefix += "!";
	prefix += get_username();
	prefix += "@";
	prefix += get_hostname();
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

bool Client::is_oper()
{
	return (this->_oper);
}

void Client::set_oper()
{
	this->_oper = true;
}

bool Client::is_registered()
{
	return (_auth && _nickname.size() && _username.size());
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

int Client::get_channel_size()
{
	return (_channels.size());
}

Channel* Client::get_last_channel()
{
	if (get_channel_size() == 0)
		return (NULL);
	return (_channels.back());
}

void Client::message_client(std::string message)
{
	if (message.find("\r\n"))
		message += "\r\n";
	if (send(this->get_socket_fd(), message.c_str(), strlen(message.c_str()), 0) == -1)
		throw std::runtime_error("Could't send messageUser");
}

bool Client::set_flag(char c, bool is_on)
{
	if (this->_mode.find(c) != this->_mode.end() && this->_mode[c] != is_on)
	{
		this->_mode[c] = is_on;
		return (true);
	}
	return (false);
}
