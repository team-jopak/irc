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

class Message;
class Command;
class Client;
class Channel;

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

    // 서버 관련 함수    
    std::string get_password();
    Client*     find_client(int fd);

    // 클라이언트 관련 함수
    std::list<Client *> get_clients();
    Client *get_client_by_socket_fd(int socket_fd);
    void delete_client(int socket_fd);


    void message_all(std::string message);

};

#include "Channel.hpp"
#include "Message.hpp"

#endif
