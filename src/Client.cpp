#include "../include/Client.hpp"

Client::Client(int client_fd)
{
	this->_client_fd = client_fd;
	this->_nickname = "";
	this->_auth = false;
};

Client::~Client()
{
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

void Client::add_channel(Channel *channel)
{
	std::list<Channel *>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if ((*it)->get_name() == channel->get_name())
			return;
	}
	_channels.push_back(channel);
	channel->add_client(this);
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

