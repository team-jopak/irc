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

    std::string get_str();
    std::string get_ch_mode(Channel* ch);

    void        set_space();
    void        set_prefix();
    void        set_string(std::string str);
    void        set_number(std::string num_str);
    void        set_nickname(Client* client);
    void        set_client_prefix(Client* client);
    void        set_ch_name(Channel* ch);
    void        set_colon_msg(std::string msg);
    void        set_clients_nickname(Channel* ch, Ch_client* clients);

    void        send_client(Client* client);
    void        send_client_exec(Client* client, std::string cmd);
    void        send_channel(Channel* ch);
    void        send_channel_exec(Channel* ch, Client* client, std::string cmd);

    void        liststart_321(Client* client);
    void        list_322(Client* client, std::string ch_name);
    void        listend_323(Client* client);
    void        topic_332(Client* client, Channel* ch);
    void        clock_333(Client* client, Channel* ch);
    void        namreply_353(Client* client, Channel* ch);
    void        endofnames_366(Client* client, Channel* ch);
};

#include "Server.hpp"

#endif
