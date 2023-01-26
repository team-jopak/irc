#ifndef CLIENTS_HPP
# define CLIENTS_HPP

#include <iostream>
// #include <cctype>
#include "Channel.hpp"

class Channel;

class Client
{
private:
    int         _client_fd;
    std::string _nickname;
    std::string _username;
    std::string _realname;
    bool _auth;
    std::list<Channel *> _channels;

public:
    Client(int client_fd);
    ~Client();
    
    int get_socket_fd();
    std::string get_nickname();
    std::string get_username();
    std::string get_realname();
    void set_nickname(std::string );
    void set_username(std::string _username);
    void set_realname(std::string _username);
    bool is_auth();
    void auth();
    void add_channel(Channel *channel);
    void delete_channel(Channel *channel);
    void message_client(std::string message);


};

#endif