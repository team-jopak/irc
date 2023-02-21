#ifndef REPLY_HPP
# define REPLY_HPP

#include <sstream>
#include <map>
#include <time.h> // clock

class Server;
class Channel;
class Ch_client;
class Client;

class Reply
{
private:
    typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;

    std::stringstream   _ss;
    Server*             _server;

public:
    Reply(Server* server);
    ~Reply();

    void        init_ss();

    std::string get_channel_mode(Channel* ch);

    void        set_space();
    void        set_server_prefix();
    void        set_client_prefix(Client* client);
    void        set_msg(std::string str);
    void        set_client_name(Client* client);
    void        set_client_name(Ch_client* clients, Channel* ch);
    void        set_channel_name(Channel* ch);

    void        send_client(Client* client);
    void        send_client_exec(Client* client, std::string cmd);
    void        send_channel(Channel* ch);
    void        send_channel_except(Channel* ch, Client* client);
    void        send_channel_exec(Channel* ch, Client* client, std::string cmd);
    void        send_channel_exec_except(Channel* ch, Client* client, std::string cmd);

    void        welcome_001(Client* client);
    void        away_301(Client* client, Channel* ch, Client* tar);
    void        liststart_321(Client* client);
    void        list_322(Client* client, std::string ch_name);
    void        channelmodeis_324(Client* client, Channel* ch);
    void        listend_323(Client* client);
    void        topic_332(Client* client, Channel* ch);
    void        clock_333(Client* client, Channel* ch);
    void        inviting_341(Client* client, Channel* ch, std::string tar_cli);
    void        namreply_353(Client* client, Channel* ch);
    void        endofnames_366(Client* client, Channel* ch);
    void        banlist_367(Client* client, Channel* ch, std::string banid);
    void        endofbanlist_368(Client* client, Channel* ch);
};

#include "Server.hpp"

#endif
