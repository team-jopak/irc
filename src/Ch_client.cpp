#include "../include/Ch_client.hpp"

std::map<std::string, Client *>::iterator	Ch_client::begin()
{
	return (clients.begin());
}

std::map<std::string, Client *>::iterator	Ch_client::end()
{
	return (clients.end());
}

Client* Ch_client::get(std::string nickname)
{
	map_client_iter result = clients.find(nickname);

	return (result != clients.end() ? result->second : NULL);
}

bool Ch_client::add(Client* client)
{
	std::pair<map_client_iter, bool>    result;
	std::string                         nickname = client->get_nickname();

	result = clients.insert(std::pair<std::string, Client *>(nickname, client));
	return (result.second);
}

void Ch_client::set(Client* client)
{
	std::string nickname = client->get_nickname();

	if (clients.find(nickname) != clients.end())
	{
		clients[nickname] = client;
	}
}

bool Ch_client::del(Client* client)
{
	std::string nickname = client->get_nickname();

	if (exist(client))
	{
		clients.erase(nickname);
		return (true);
	}
	return (false);
}

bool Ch_client::exist(Client* client)
{
	return (get(client->get_nickname()) != NULL);
}

int Ch_client::size()
{
	return (clients.size());
}

bool Ch_client_ban::add(std::string mask, Client* client)
{
	std::pair<map_client_iter, bool>	result;

	result = clients.insert(std::pair<std::string, Client*>(mask, client));
	if (result.second)
		times.insert(std::pair<std::string, clock_t>(mask, clock()));
	return (result.second);
}

void Ch_client_ban::set(std::string mask, Client* client)
{
	if (clients.find(mask) != clients.end())
	{
		clients[mask] = client;
		times[mask] = clock();
	}
}

bool Ch_client_ban::del(std::string mask)
{
	if (get(mask) != NULL)
	{
		clients.erase(mask);
		times.erase(mask);
		return (true);
	}
	return (false);
}

clock_t Ch_client_ban::time(std::string mask)
{
	Client* client = get(mask);

	return (client != NULL ? times[mask] : 0);
}

bool Ch_client_ban::exist(Client* client)
{
	map_client_iter	iter = clients.begin();
	map_client_iter end = clients.end();
	std::string		name;

	name += client->get_nickname();
	name += "!";
	name += client->get_username();
	name += "@";
	name += client->get_hostname();

	for (; iter != end; iter++)
	{
		if (ft::strmatch(iter->first, name))
			return (true);
	}
	return (false);
}
