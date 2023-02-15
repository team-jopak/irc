#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <map>
#include "Client.hpp"
#include "Exceptions.hpp"

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
	Channel(const Channel &origin);
	~Channel();

	Ch_client*	op;
	Ch_client*	joined;
	Ch_client*	invited;
	Ch_client*	banned;
	Ch_client*	voice;
	
	std::string	get_name();
	std::string get_topic();
	std::string	get_key();
	list_client	get_clients();
	std::string	get_flag_str(Client* client);
	
	void		set_limit(int limit);
	void 		set_topic(std::string topic);
	void		set_key(std::string key);
	void		set_flag(char c, bool is_on);
	void		add_mask(std::string mask);

	bool		check_key(std::string key);
	bool		check_flag(char c);
	bool		check_limit();
	bool		is_talkable(Client *client);
	
	void		init_flags();
	void		join(Client* client, std::string pass);
	void		leave(Client* client);

	void		message_channel(std::string message);
	void 		message_channel_with_prefix(std::string message);
};

#include "Ch_client.hpp"

#endif
