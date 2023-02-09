#include "../include/Reply.hpp"

Reply::Reply(Server* server) : _server(server)
{}

Reply::~Reply()
{}

void Reply::init_ss()
{
    _ss.str("");
}

std::string Reply::get_str()
{
    return (_ss.str());
}

void Reply::set_space()
{
    _ss << " ";
}

void Reply::set_string(std::string str)
{
    _ss << str;
    set_space();
}

void Reply::set_number(std::string num_str)
{
    _ss << num_str;
    set_space();
}

void Reply::set_nickname(Client* client)
{
    _ss << client->get_nickname();
    set_space();
}

void Reply::set_client_prefix(Client* client)
{
    _ss << client->get_message_prefix();
    set_space();
}

void Reply::set_ch_name(Channel* ch)
{
    _ss << ch->get_name();
    set_space();
}

void Reply::set_colon_msg(std::string msg)
{
    _ss << ":" << msg;
    set_space();
}

void Reply::set_prefix()
{
    set_colon_msg(_server->get_name());
    set_space();
}

void Reply::set_clients_nickname(Channel* ch, Ch_client* clients)
{
    map_client_iter     iter = clients->begin();
    map_client_iter     end = clients->end();

    for (; iter != end; iter++)
    {
        std::string nick;

        if (ch->voice->exist(iter->second))
            nick = "+";
        if (ch->op->exist(iter->second))
            nick = "@";
        nick.append(iter->first);
        set_string(nick);
    }
}

void Reply::send_client(Client* client)
{
    client->message_client(_ss.str());
    init_ss();
}

void Reply::send_channel(Channel* ch)
{
    ch->message_channel(_ss.str());
    init_ss();
}

void Reply::send_channel_exec(Channel* ch, Client* client, std::string cmd)
{
    set_colon_msg(client->get_message_prefix());
    set_string(cmd);
    send_channel(ch);
}

void Reply::topic_332(Client* client, Channel* ch, std::string msg)
{
    set_prefix();
    set_number("332");
    set_nickname(client);
    set_ch_name(ch);
    set_colon_msg(msg);
    send_client(client);
}

void Reply::clock_333(Client* client, Channel* ch)
{
    set_prefix();
    set_number("333");
    set_nickname(client);
    set_ch_name(ch);
    set_client_prefix(client);
    _ss << ":" << clock();
    send_client(client);
}

void Reply::namreply_353(Client* client, Channel* ch, std::string mode)
{
    set_prefix();
    set_number("353");
    set_nickname(client);
    set_string(mode);
    set_ch_name(ch);
    _ss << ":";
    set_clients_nickname(ch, ch->joined);
    send_client(client);
}

void Reply::endofnames_366(Client* client, Channel* ch)
{
    set_prefix();
    set_number("366");
    set_nickname(client);
    if (ch == NULL)
        _ss << "*";
    else
        _ss << ch->get_name();
    set_string(" :End of /NAMES list.");
    send_client(client);
}
