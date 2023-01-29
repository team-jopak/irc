#ifndef SERVER_HPP
# define SERVER_HPP

#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <list>
#include <vector>
#include <cstring>
#include <fcntl.h> // send
#include <netdb.h> // addrinfo

#include "Channel.hpp"
#include "Client.hpp"

class Message;
class Command;

class Server
{
private:
    int _socket_fd;
    std::string _host;
    std::string _port;
    std::string _password;
    std::vector<pollfd> _poll_fd_vec;
    std::list<Client *> _clients;
    std::list<Channel *> _channels;
    Message* _message;
    Command* _cmd;

public:
    Server(std::string host, std::string port, std::string password);
    ~Server();

    void    server_run();
    int     recv_message(int cur_fd);
    int     accept_client();
    void    init();
    
    std::string get_password();

};

#include "Message.hpp"

#endif
