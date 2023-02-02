#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"
#include <map>

enum ch_mode
{
	PRIVE,	// 사설
	SCRET,	// 비밀
	INVIT,	// 초대
	MODER	// 회의
};

struct channel_flag
{
    bool o;
    bool p;
    bool s;
    bool i;
    bool t;
    bool n;
    bool b;
    bool v;
};

struct user_flag
{
    bool i;
    bool w;
    bool s;
    bool o;
};

struct Mode_flag
{
    channel_flag    ch;
    user_flag       usr;

	std::string ftos();
};

class Client;

class Channel
{
private:
	typedef std::list<Client *>				list_client;
	typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;

	std::string	_name;
	std::string	_topic;
	std::string	_password;

	Mode_flag	_mode;

	map_client	_op;
	map_client	_clients;
	map_client	_invited;
	map_client	_banned;

public:
	Channel(std::string name);
	~Channel();
	
	std::string	get_name();
	std::string	get_password();
	list_client	get_clients();

	bool		check_invitation(Client* client);
	bool		check_ban_list(Client* client);
	bool		check_password(std::string key);
	
private:
	Client*		get_client(map_client map, std::string name);
	bool		add_client(map_client map, Client *client);
	void		delete_client(map_client map, Client *client);

public:
	void		join_channel(Client* client, std::string pass);
	void		leave_channel(Client* client);
	void		set_op_client(Client* client);
	bool		check_op_client(Client* client);
	void		message_channel(std::string message);
};

#endif