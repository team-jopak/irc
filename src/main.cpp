#include "../include/Server.hpp"

#define SERVER_PORT  12345
#define HOST "127.0.0.1"
#define MSG_USAGE "ircserv: usage ./ircserv <port> <password>\n"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(STDERR_FILENO, MSG_USAGE, std::strlen(MSG_USAGE));
		return (EXIT_FAILURE);
	}
	try
	{
		Server server(HOST ,argv[1], argv[2]);
		server.server_run();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}
