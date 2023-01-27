#include "../include/Channel.hpp"

Channel::Channel(std::string name, std::string password)
    : _name(name), _password(password), _topic(name)
{    
}

Channel::~Channel()
{
}

std::list<Client *> Channel::get_clients()
{
    return _clients;
}

std::string Channel::get_name()
{
    return _name;
}

void Channel::add_client(Client *client)
{
    for (std::list<Client *>::iterator it = _clients.begin();
        it != _clients.end(); ++it)
    {
        if ((*it)->get_nickname() == client->get_nickname())
        {
            return ;
        }
    }
}

std::string Channel::get_password()
{
    return _password;
}

void Channel::message_channel(std::string message)
{
    if (message.find("\r\n"))
        message += "\r\n";
    for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (send((*it)->get_socket_fd(), message.c_str(), strlen(message.c_str()), 0) == -1)
            throw std::runtime_error("Couldn't send message_channel");
    }
}

Client *Channel::get_client_by_nickname(std::string name)
{
    for (std::list<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (name == (*it)->get_nickname())
        {
            return *it;
        }
    }
    return NULL;
}

void Channel::delete_client(Client *client)
{
    for (std::list<Client *>::iterator it = _clients.begin();
        it != _clients.end(); ++it)
    {
        if (*it == client)
        {
            _clients.erase(it);
            return ;
        }
    }
}