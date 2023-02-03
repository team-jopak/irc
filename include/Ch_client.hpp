#ifndef CH_CHLIENT_HPP
# define CH_CHLIENT_HPP

#include "Client.hpp"

class Ch_client
{
public:
	typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;

	map_client	clients;

	map_client_iter	begin();
	map_client_iter	end();
	Client* 		get(std::string nickname);
	bool 			add(Client* client);
	void 			set(Client* client);
	void 			del(Client* client);
	bool 			exist(Client* client);
};

#endif