#include "../include/Channel.hpp"

Channel::Channel(std::string name)
    : _name(name), _topic(name)
{
    init_flags();
}

Channel::~Channel()
{
}

void Channel::init_flags()
{
    this->_mode.clear();
    this->_mode['p'] = false;
    this->_mode['s'] = false;
    this->_mode['i'] = false;
    this->_mode['n'] = false;
    this->_mode['m'] = false;
    this->_mode['k'] = false;
}

void Channel::set_flag(char c, bool is_on)
{
    if (this->_mode.find(c) != this->_mode.end())
        this->_mode[c] = is_on;
}

bool Channel::add_mask(std::string mask)
{
    _masks.push_back(mask);
}

std::list<Client *> Channel::get_clients()
{
    map_client_iter iter = clients->begin();
    map_client_iter end = clients->end();
    list_client     list_client;

    for (; iter != end; iter++)
        list_client.push_back(iter->second);
    return list_client;
}

std::string Channel::get_name()
{
    return _name;
}

std::string Channel::get_topic()
{
    return _topic;
}

std::string Channel::get_key()
{
    return _key;
}

std::string Channel::get_flag_str(Client* client)
{
    map_flag::iterator  iter = _mode.begin();
    map_flag::iterator  end = _mode.end();
    std::string         result = "[+";

    for (; iter != end; iter++)
    {
        if (iter->second)
            result.push_back(iter->first);
    }
    if (this->_key.size() > 0)
    {
        result.push_back(' ');
        if (this->clients->exist(client))
            result.append(_key);
        else
            result.append("<key>");
    }
    result.push_back(']');
    return (result);
}

bool Channel::check_key(std::string key)
{
    return (key == this->_key);
}

bool Channel::check_flag(char c)
{
    std::map<char, bool>::iterator iter = this->_mode.find(c);

    if (iter != this->_mode.end())
        return (iter->second);
    return false;
}

void Channel::set_limit(int limit)
{
    this->_limit = limit;
}

void Channel::set_topic(std::string topic)
{
    this->_topic = topic;
}

void Channel::set_key(std::string key)
{
    this->_key = key;
}

void    Channel::join(Client* client, std::string pass)
{
    // _mode에 따라서 확인한다.

    // switch (this->_mode)
    // {
    // case SCRET:
    //     if (!check_key(pass))
    //     {
    //         // 비밀 번호 틀림
    //         return ;
    //     }

    // case INVIT:
    //     if (!invited.exist(client))
    //     {
    //         // 초대 받지 않음
    //         return ;
    //     }
    // default:;
    // }

    (void)pass;
    if (banned->exist(client) && !invited->exist(client))
    {
        // banned이고, 초대받지 않음
        return ;
    }

    invited->del(client);
    clients->add(client);
    client->add_channel(this);
}

void Channel::leave(Client* client)
{
    clients->del(client);
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

void Channel::message_channel_with_prefix(std::string message)
{
    list_client clients = get_clients();

    if (message.find("\r\n"))
        message += "\r\n";
    for (list_client::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        std::string full_msg = (*it)->get_message_prefix();
        full_msg += message;
        if (send((*it)->get_socket_fd(), message.c_str(), strlen(message.c_str()), 0) == -1)
            throw std::runtime_error("Couldn't send message_channel");
    }
}