#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Server.hpp"
#include "Client.hpp"

class Server;
class Client;

class Channel
{
private:
    std::string _name;
    std::list<Client *> _clients;
    std::string _password;
    std::string _topic;

public:
    Channel(std::string name, std::string password);
    ~Channel();
    
    std::string get_name();
    void add_client(Client *client);
    std::string get_password();
    std::list<Client *> get_clients();
    Client *get_client_by_nickname(std::string name);
    void message_channel(std::string message);
    void delete_client(Client *client);
};

#endif