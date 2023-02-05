#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <map>
#include "Client.hpp"

class Client;
class Ch_client;

class Channel
{
private:
	typedef std::list<std::string>			list_str;
	typedef std::list<Client *>				list_client;
	typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;
	typedef std::map<char, bool>			map_flag;

	std::string	_name;
	std::string	_topic;
	std::string	_key;
	map_flag	_mode;
	int			_limit;
	list_str	_masks;

public:
	Channel(std::string name);
	~Channel();

	Ch_client*	op;
	Ch_client*	clients;
	Ch_client*	invited;
	Ch_client*	banned;
	Ch_client*	voice;
	
	std::string	get_name();
	std::string	get_key();
	list_client	get_clients();

	void		set_limit(int limit);
	void		set_key(std::string key);
	void		set_flag(char c, bool is_on);
	bool		add_mask(std::string mask);

	bool		check_key(std::string key);
	
	void		init_flags();
	void		join(Client* client, std::string pass);
	void		leave(Client* client);

	void		message_channel(std::string message);
};

#include "Ch_client.hpp"

#endif
