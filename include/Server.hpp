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
#include "Reply.hpp"

class Message;
class Command;
class Client;
class Channel;

class Server
{
private:;
    int _socket_fd;
    std::string _host;
    std::string _port;
    std::string _password;
    std::vector<pollfd> _poll_fd_vec;
    std::list<Client *> _clients;
    std::list<Channel *> _channels;
    Message*            _message;
    Command*            _cmd;

public:
    Reply*              reply;

    Server(std::string host, std::string port, std::string password);
    ~Server();

    void    server_run();
    int     recv_message(int cur_fd);
    int     accept_client();
    void    init();

    // 서버 관련 함수    
    std::string get_password();
    std::string get_host();
    Client*     find_client(int fd);

    // 클라이언트 관련 함수
    std::list<Client *>     get_clients();
    Client*                 get_client_by_socket_fd(int socket_fd);
    Client*                 get_client_by_nickname(std::string nickname);
    void                    delete_client(int socket_fd);

    // 채널 관련 함수
	void                    add_channel(std::string name, Client* client);
    std::list<Channel *>	get_channel_list();
    std::list<Channel *>	get_channel_list(Client* client);
    Channel*            	get_channel(std::string name);

    void message_all(std::string message);

    // 에러 관련 함수
    void serverResponse(std::string message, int client_fd);
};

#include "Channel.hpp"
#include "Message.hpp"

#endif
