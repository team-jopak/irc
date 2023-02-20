#include "../include/Tcpflow.hpp"

Tcpflow::Tcpflow()
{
}

// server -> client(fd) : [ msg ]
void Tcpflow::to_client(Client* client, std::string msg)
{
    std::cout << "server -> client(" << client->get_socket_fd() << "): " << msg << "\n" << std::endl;
}

// client(fd) -> server : [ msg ]
void Tcpflow::to_server(Client* client, std::string msg)
{
    std::cout << "client(" << client->get_socket_fd() << ") -> server: " << msg << std::endl;
}  
