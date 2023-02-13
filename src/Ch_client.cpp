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

	result = clients.insert(std::pair<const std::string, Client *>(nickname, client));
	return (result.second);
}

void Ch_client::set(Client* client)
{
	std::string nickname = client->get_nickname();

	if (clients.find(nickname) != clients.end())
		clients[nickname] = client;
}

bool Ch_client::del(Client* client)
{
	if (exist(client))
	{
		clients.erase(client->get_nickname());
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
