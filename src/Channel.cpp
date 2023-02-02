#include "../include/Channel.hpp"

Channel::Channel(std::string name)
    : _name(name), _topic(name)
{    
}

Channel::~Channel()
{
}

std::list<Client *> Channel::get_clients()
{
    map_client_iter iter = _clients.begin();
    map_client_iter end = _clients.end();
    list_client     clients;

    for (; iter != end; iter++)
        clients.push_back(iter->second);
    return clients;
}

std::string Channel::get_name()
{
    return _name;
}

std::string Channel::get_password()
{
    return _password;
}

void Channel::message_channel(std::string message)
{
    list_client clients = get_clients();

    if (message.find("\r\n"))
        message += "\r\n";
    for (list_client::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (send((*it)->get_socket_fd(), message.c_str(), strlen(message.c_str()), 0) == -1)
            throw std::runtime_error("Couldn't send message_channel");
    }
}

Client* Channel::get_client(map_client map, std::string name)
{
    map_client_iter result = map.find(name);

    return (result != map.end() ? result->second : NULL);
}

bool    Channel::check_invitation(Client* client)
{
    return (get_client(_invited, client->get_nickname()) != NULL);
}

bool    Channel::check_ban_list(Client* client)
{
    return (get_client(_banned, client->get_nickname()) != NULL);
}

bool    Channel::check_password(std::string key)
{
    return (key == this->_password);
}

bool Channel::add_client(map_client map, Client *client)
{
    std::pair<map_client_iter, bool>    result;
    std::string                         nickname = client->get_nickname();

    result = map.insert(std::pair<std::string, Client *>(nickname, client));
    return (result.second);
}

void Channel::delete_client(map_client map, Client *client)
{
    map.erase(client->get_nickname());
}

void    Channel::join_channel(Client* client, std::string pass)
{
    switch (_mode)
    {
    case SCRET:
        if (!check_password(pass))
        {
            // 비밀 번호 틀림
            return ;
        }

    case INVIT:
        if (!check_invitation(client))
        {
            // 초대 받지 않음
            return ;
        }
    default:;
    }

    if (check_ban_list(client) && !check_invitation(client))
    {
        // banned이고, 초대받지 않음
        return ;
    }

    delete_client(_invited, client);
    add_client(_clients, client);
    client->add_channel(this);
}

void    Channel::leave_channel(Client* client)
{
    delete_client(_clients, client);
}

void Channel::set_op_client(Client* client)
{
    add_client(_op, client);
}

bool Channel::check_op_client(Client* client)
{
    return (get_client(_op, client->get_nickname()) != NULL);
}