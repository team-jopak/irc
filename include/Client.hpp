#ifndef CLIENTS_HPP
# define CLIENTS_HPP

// #include <fcntl.h>
#include <sys/socket.h>
#include <iostream>
#include <list>
#include "Channel.hpp"

class Channel;

class Client
{
private:
    std::string             _nickname;
    std::string             _username;
    std::string             _realname;
    bool                    _auth;
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
    void add_channel(Channel *channel);
    void delete_channel(Channel *channel);
    void message_client(std::string message);


};

#endif
