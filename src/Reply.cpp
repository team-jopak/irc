#include "../include/Reply.hpp"

Reply::Reply(Server* server) : _server(server)
{}

Reply::~Reply()
{}

void Reply::init_ss()
{
    _ss.str("");
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

void Reply::set_client_prefix(Client* client)
{
    _ss << client->get_message_prefix();
    set_space();
}

void Reply::set_server_prefix()
{
    set_msg(":" + _server->get_name());
    set_space();
}

void Reply::set_channel_name(Channel* ch)
{
    _ss << ch->get_name();
    set_space();
}

void Reply::set_client_name(Client* client)
{
    _ss << client->get_nickname();
    set_space();
}

void Reply::set_client_name(Ch_client* clients, Channel* ch)
{
    map_client_iter     iter = clients->begin();
    map_client_iter     end = clients->end();
    std::string         nick;

    for (; iter != end; iter++)
    {
        nick = "";
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
    set_msg(":" + client->get_message_prefix());
    set_msg(cmd);
    send_client(client);
    init_ss();
}

void Reply::send_channel(Channel* ch)
{
    std::string msg = _ss.str();

    msg.pop_back();
    ch->message_channel(msg);
    init_ss();
}

void Reply::send_channel_except(Channel* ch, Client* client)
{
    std::string msg = _ss.str();
    
    msg.pop_back();
    ch->message_channel_except_sender(msg, client);
    init_ss();
}

void Reply::send_channel_exec(Channel* ch, Client* client, std::string cmd)
{
    set_msg(":" + client->get_message_prefix());
    set_msg(cmd);
    send_channel(ch);
    init_ss();
}

void Reply::send_channel_exec_except(Channel* ch, Client* client, std::string cmd)
{
    set_msg(":" + client->get_message_prefix());
    set_msg(cmd);
    send_channel_except(ch, client);
    init_ss();
}

void Reply::welcome_001(Client* client)
{
    set_server_prefix();
    set_client_name(client);
    set_msg(":Welcome to the Localnet IRC Network");
    set_client_name(client);
    send_client(client);
}

void Reply::liststart_321(Client* client)
{
    set_server_prefix();
    set_msg("321");
    set_client_name(client);
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

    ch_opt = "[" + ch_opt + "]";
    if (!is_joined && ch->check_flag('s'))
        return ;
    else if (!is_joined && ch->check_flag('p'))
    {
        ch_name = "*";
        ch_opt = "";
        ch_topic = "";
    }

    set_server_prefix();
    set_msg("322");
    set_client_name(client);
    set_msg(ch_name);
    set_msg(std::to_string(ch->joined->size()));
    set_msg(":" + ch_opt);
    set_msg(ch_topic);
    send_client(client);
}

void Reply::listend_323(Client* client)
{
    set_server_prefix();
    set_msg("323");
    set_client_name(client);
    set_msg(":End of channel list.");
    send_client(client);
}

void Reply::channelmodeis_324(Client* client, Channel* ch)
{
    std::string                 ch_mode = ch->get_flag_str(client);
    std::vector<std::string>    opts = ft::split_vec(ch_mode, ' ');

    opts[opts.size() - 1] = ":" + opts[opts.size() - 1];
    set_server_prefix();
    set_msg("324");
    set_client_name(client);
    set_channel_name(ch);
    set_msg(ft::vec_str_join(opts, " "));
    send_client(client);
}

void Reply::topic_332(Client* client, Channel* ch)
{
    set_server_prefix();
    set_msg("332");
    set_client_name(client);
    set_channel_name(ch);
    set_msg(":" + ch->get_topic());
    send_client(client);
}

void Reply::clock_333(Client* client, Channel* ch)
{
    set_server_prefix();
    set_msg("333");
    set_client_name(client);
    set_channel_name(ch);
    set_client_prefix(client);
    _ss << ":" << clock();
    send_client(client);
}

void Reply::namreply_353(Client* client, Channel* ch)
{
    set_server_prefix();
    set_msg("353");
    set_client_name(client);
    set_msg(get_channel_mode(ch));
    set_channel_name(ch);
    _ss << ":";
    set_client_name(ch->joined, ch);
    send_client(client);
}

void Reply::endofnames_366(Client* client, Channel* ch)
{
    set_server_prefix();
    set_msg("366");
    set_client_name(client);
    if (ch == NULL)
        _ss << "*";
    else
        _ss << ch->get_name();
    set_msg(" :End of /NAMES list.");
    send_client(client);
}

void Reply::banlist_367(Client* client, Channel* ch, std::string banid)
{
    set_server_prefix();
    set_msg("367");
    set_client_name(client);
    set_channel_name(ch);
    set_msg(banid);
    set_msg(ch->banned->get(banid)->get_nickname());
    set_msg(":" + ft::ltos(ch->banned->time(banid)));
    send_client(client);
}

void Reply::endofbanlist_368(Client* client, Channel* ch)
{
    set_server_prefix();
    set_msg("368");
    set_client_name(client);
    set_channel_name(ch);
    set_msg(":End of channel ban list");
    send_client(client);
}
