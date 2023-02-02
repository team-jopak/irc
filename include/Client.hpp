#ifndef CLIENTS_HPP
# define CLIENTS_HPP

#include <iostream>
#include "Channel.hpp"
// #include <fcntl.h>
#include <sys/socket.h>
#include <list>


class Channel;

class Client
{
private:
    std::string             _nickname;
    std::string             _username;
    std::string             _realname;
    bool                    _auth;
    bool                    _oper;
    std::list<Channel *>    _channels;

public:
    int                     _client_fd;
    
    Client(int client_fd);
    ~Client();
    
    int get_socket_fd();
    std::string get_nickname();
    std::string get_username();
    std::string get_realname();
    void set_nickname(std::string nickname);
    void set_username(std::string username);
    void set_realname(std::string realname);
    bool is_auth();
    void set_auth();
    bool is_oper();
    void set_oper();
    void add_channel(Channel *channel);
    void delete_channel(Channel *channel);
    void message_client(std::string message);


};

#endif