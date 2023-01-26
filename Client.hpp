#ifndef CLIENTS_HPP
# define CLIENTS_HPP

#include <iostream>
// #include <cctype>
#include <iostream>


class Client
{
private:
    std::string _nickname;
    std::string _username;
    std::string _realname;
    bool _auth;


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

};