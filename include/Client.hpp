#ifndef CLIENTS_HPP
# define CLIENTS_HPP

// #include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>
#include <iostream>
#include <list>
#include "Channel.hpp"

class Channel;

class Client
{
private:
    typedef std::map<char, bool>    map_flag;
    typedef std::list<Channel *>	list_channel;

    std::string     _nickname;
    std::string     _username;
    std::string     _hostname;
    std::string     _servername;
    std::string     _realname;
    bool            _auth;
    bool            _oper;
    list_channel    _channels;
    map_flag        _mode;

public:
    int             _client_fd;
    
    Client(int client_fd);
    Client(const Client &origin);
    ~Client();
    
    int				get_socket_fd();
    std::string		get_nickname();
    std::string		get_username();
    std::string		get_hostname();
    std::string		get_servername();
    std::string		get_realname();
    std::string		get_message_prefix();

    void			set_nickname(std::string nickname);
    void			set_username(std::string username);
    void			set_hostname(std::string hostname);
    void			set_servername(std::string servername);
    void			set_realname(std::string realname);
    void			set_auth();
    void			set_oper();

    bool			is_auth();
    bool			is_oper();

    void			add_channel(Channel *channel);
    void			delete_channel(Channel *channel);

    void			message_client(std::string message);

    void			set_flag(char c, bool is_on);
};

#endif
