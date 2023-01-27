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
// #include "Exceptions.hpp"

#include "Channel.hpp"
#include "Client.hpp"

class Client;
class Channel;

class Server
{
private:
    std::string _host;
    std::string _port;
    std::string _password;
    int _socket_fd;
    std::vector<pollfd> _poll_fd_vec;
    std::list<Client *> _clients;
    std::list<Channel *> _channels;

public:
    Server(std::string host, std::string port, std::string password);
    ~Server();

    void    server_run();
    int     recv_message(int cur_fd);
    int     accept_client();
    void    init();

};

#endif