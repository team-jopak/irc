#include "../include/Channel.hpp"

Channel::Channel(std::string name) : _name(name), _topic("")
{
    init_flags();
    this->_mode['n'] = true;
    this->_mode['t'] = true;
    this->op = new Ch_client();
    this->joined = new Ch_client();
    this->invited = new Ch_client();
    this->voice = new Ch_client();
    this->banned = new Ch_client_ban();
}

Channel::~Channel()
{
    delete this->op;
    delete this->joined;
    delete this->invited;
    delete this->banned;
    delete this->voice;
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
    this->_mode['l'] = false;
}

bool Channel::set_flag(char c, bool is_on)
{
    if (this->_mode.find(c) != this->_mode.end() && this->_mode[c] != is_on)
    {
        this->_mode[c] = is_on;
        return (true);
    }
    return (false);
}

bool Channel::add_mask(std::string mask)
{
    std::pair<set_str::iterator, bool> result = _masks.insert(mask);
    
    return (result.second);
}

std::list<Client *> Channel::get_clients()
{
    map_client_iter iter = joined->begin();
    map_client_iter end = joined->end();
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
    std::string         result = "+";

    for (; iter != end; iter++)
    {
        if (iter->second)
            result.push_back(iter->first);
    }
    if (check_flag('k'))
    {
        result.push_back(' ');
        if (this->joined->exist(client))
            result.append(_key);
        else
            result.append("<key>");
    }
    if (check_flag('l'))
    {
        result.push_back(' ');
        result.append(ft::ltos(_limit));
    }
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
    return (false);
}

bool Channel::check_limit()
{
    return (this->joined->size() < this->_limit);
}

bool Channel::is_talkable(Client *client)
{
    if (check_flag('n') && !joined->exist(client))
        return (false);
    if (check_flag('m') && !voice->exist(client))
        return (false);
    return (true);
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

// key이지만 invited라면 무조건 들어올 수 있다.
// invited가 아닌경우 key를 확인한다.
// invited가 아니고, key도 아닌 경우 key error
// invited가 아니고, key가 맞은 경우 invited error
void    Channel::join(Client* client, std::string pass)
{
    if (!invited->exist(client))
    {
        if (check_flag('k') && !check_key(pass))
            throw Err_475(get_name());

        if (check_flag('i') && !invited->exist(client))
            throw Err_473(get_name());

        if (check_flag('l') && check_limit())
            throw Err_471(get_name());

        if (banned->exist(client))
            throw Err_474(get_name());
    }
    invited->del(client);
    joined->add(client);
    client->add_channel(this);
}

void Channel::leave(Client* client)
{
    op->del(client);
    joined->del(client);
    invited->del(client);
    voice->del(client);
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

void Channel::message_channel_except_sender(std::string message, Client *sender)
{
    list_client clients = get_clients();

    if (message.find("\r\n"))
        message += "\r\n";
    for (list_client::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if ((*it) == sender)
            continue;
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
