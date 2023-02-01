#include "../include/Server.hpp"

#define SERVER_PORT  12345
#define HOST "127.0.0.1"

#define TRUE             1
#define FALSE            0

int main(int argc, char **argv)
{
	(void)argc;

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
