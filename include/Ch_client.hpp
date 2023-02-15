#ifndef CH_CHLIENT_HPP
# define CH_CHLIENT_HPP

#include "Client.hpp"
#include <time.h>

class Ch_client
{
private:
	typedef std::map<std::string, clock_t>	map_time;
	typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;

	map_client		clients;
	map_time		times;

public:
	map_client_iter	begin();
	map_client_iter	end();
	Client* 		get(std::string nickname);
	clock_t			time(std::string nickname);
	bool 			add(Client* client);
	void 			set(Client* client);
	bool 			del(Client* client);
	bool 			exist(Client* client);
	int				size();
};

#endif
