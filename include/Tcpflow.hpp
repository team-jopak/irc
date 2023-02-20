#ifndef TCPFLOW_HPP
# define TCPFLOW_HPP
#include <iostream>

class Client;

class Tcpflow
{
public:
    Tcpflow();
    void to_client(Client* client, std::string msg);
    void to_server(Client* client, std::string msg);
};

#include "Client.hpp"

#endif