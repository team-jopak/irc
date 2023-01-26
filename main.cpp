#include "Server.hpp"

#include "Command.hpp"
#include "Message.hpp"

#define SERVER_PORT  12345
#define HOST "127.0.0.1"

#define TRUE             1
#define FALSE            0

int main(int argc, char **argv)
{

	Server server(HOST ,argv[1], argv[2]);
	server.server_run();
	
  return (0);
}
