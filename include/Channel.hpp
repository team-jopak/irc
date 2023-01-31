#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <list>
#include "Client.hpp"

class Client;

class Channel
{
private:
    std::string         _name;
    std::string	        _topic;
    std::string	        _password;
    std::string         _mode;

    Client*             _admin;
    std::list<Client *>	_clients;
    std::list<Client *> _invited;
    std::list<Client *> _banned;
    

public:
    Channel(std::string name);
    ~Channel();
    
    std::string			get_name();
    std::string			get_password();

    void				add_client(Client *client);
    std::list<Client *>	get_clients();
    Client				*get_client_by_nickname(std::string name);
    void				delete_client(Client *client);

    void                set_admin_client(Client* client);

    bool                check_invitation(Client* client);
    bool                check_ban_list(Client* client);
    bool                check_password(std::string key);
	
    void                join_channel(Client* client, std::string pass);
    void                join_channel(Client* client);
    void				message_channel(std::string message);
};

#endif