#ifndef SERVER_HPP
# define SERVER_HPP

#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>

class Server
{
private:
    std::string host_;
    std::string port_;
    std::strong password;
    int socket_;
    std::vector<pollfd> pollFdVec_;
    std::list<User *> users_;
    std::list<Channel *> channels_;

public:
    Server(std::string host, std::string port, std::string password);
    ~Server();

    void init();
    void run();

};

#endif