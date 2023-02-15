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

std::string Reply::get_channel_mode(Channel* ch)
{
    std::string mode = "=";

    if (ch->check_flag('p'))
        mode = "*";
    if (ch->check_flag('s'))
        mode = "@";
    return (mode);
}

void Reply::set_space()
{
    _ss << " ";
}

void Reply::set_msg(std::string msg)
{
    _ss << msg;
    set_space();
}

void Reply::set_msg_colon(std::string msg)
{
    _ss << ":" << msg;
    set_space();
}

void Reply::set_rpl_number(std::string num_str)
{
    _ss << num_str;
    set_space();
}

void Reply::set_client_prefix(Client* client)
{
    _ss << client->get_message_prefix();
    set_space();
}

void Reply::set_channel_name(Channel* ch)
{
    _ss << ch->get_name();
    set_space();
}

void Reply::set_prefix()
{
    set_msg_colon(_server->get_name());
    set_space();
}

void Reply::set_client_nickname(Client* client)
{
    _ss << client->get_nickname();
    set_space();
}

void Reply::set_client_nickname(Ch_client* clients, Channel* ch)
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
        set_msg(nick);
    }
}

void Reply::send_client(Client* client)
{
    std::string msg = _ss.str();
    
    msg.pop_back();
    client->message_client(msg);
    init_ss();
}

void Reply::send_client_exec(Client* client, std::string cmd)
{
    set_msg_colon(client->get_message_prefix());
    set_msg(cmd);
    send_client(client);
    init_ss();
}

void Reply::send_channel(Channel* ch)
{
    ch->message_channel(_ss.str());
    init_ss();
}

void Reply::send_channel_except(Channel* ch, Client* client)
{
    Server::list_client         clients = ch->get_clients();
    Server::list_client_iter    iter = clients.begin();
    Server::list_client_iter    end = clients.end();
    std::string                 msg = _ss.str();
    
    msg.pop_back();
    for (; iter != end; iter++)
    {
        if (*iter != client)
            (*iter)->message_client(msg);
    }
    init_ss();
}

void Reply::send_channel_exec_except(Channel* ch, Client* client, std::string cmd)
{
    set_msg_colon(client->get_message_prefix());
    set_msg(cmd);
    send_channel_except(ch, client);
    init_ss();
}

void Reply::send_channel_exec(Channel* ch, Client* client, std::string cmd)
{
    set_msg_colon(client->get_message_prefix());
    set_msg(cmd);
    send_channel(ch);
    init_ss();
}

void Reply::liststart_321(Client* client)
{
    set_prefix();
    set_rpl_number("321");
    set_client_nickname(client);
    set_msg("Channel :Users Name");
    send_client(client);
}

void Reply::list_322(Client* client, std::string ch_name)
{
    Channel*    ch = _server->get_channel(ch_name);
    if (ch == NULL)
        return ;
    std::string ch_opt = ch->get_flag_str(client);
    std::string ch_topic = ch->get_topic();
    bool        is_joined = ch->joined->exist(client);

    if (!is_joined && ch->check_flag('s'))
        return ;
    else if (!is_joined && ch->check_flag('p'))
    {
        ch_name = "*";
        ch_opt = "";
        ch_topic = "";
    }

    set_prefix();
    set_rpl_number("322");
    set_client_nickname(client);
    set_msg(ch_name);
    set_msg(std::to_string(ch->joined->size()));
    set_msg_colon(ch_opt);
    set_msg(ch_topic);
    send_client(client);
}

void Reply::listend_323(Client* client)
{
    set_prefix();
    set_rpl_number("323");
    set_client_nickname(client);
    set_msg(":End of channel list.");
    send_client(client);
}

void Reply::topic_332(Client* client, Channel* ch)
{
    set_prefix();
    set_rpl_number("332");
    set_client_nickname(client);
    set_channel_name(ch);
    set_msg_colon(ch->get_topic());
    send_client(client);
}

void Reply::clock_333(Client* client, Channel* ch)
{
    set_prefix();
    set_rpl_number("333");
    set_client_nickname(client);
    set_channel_name(ch);
    set_client_prefix(client);
    _ss << ":" << clock();
    send_client(client);
}

void Reply::namreply_353(Client* client, Channel* ch)
{
    set_prefix();
    set_rpl_number("353");
    set_client_nickname(client);
    set_msg(get_channel_mode(ch));
    set_channel_name(ch);
    _ss << ":";
    set_client_nickname(ch->joined, ch);
    send_client(client);
}

void Reply::endofnames_366(Client* client, Channel* ch)
{
    set_prefix();
    set_rpl_number("366");
    set_client_nickname(client);
    if (ch == NULL)
        _ss << "*";
    else
        _ss << ch->get_name();
    set_msg(" :End of /NAMES list.");
    send_client(client);
}

void Reply::banlist_367(Client* client, Channel* ch, std::string banid)
{
    set_prefix();
    set_rpl_number("367");
    set_client_nickname(client);
    set_channel_name(ch);
    set_msg(banid);
}

void Reply::banlist_368(Client* client, Channel* ch)
{
    set_prefix();
    set_rpl_number("368");
    set_client_nickname(client);
    set_channel_name(ch);
    set_msg(":End of channel ban list");
}
