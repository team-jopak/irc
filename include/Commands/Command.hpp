#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "../util_funcs.hpp"

class Server;
class Client;
class Channel;

class Command
{
public:
    typedef std::list<std::string>          list_str;
    typedef list_str::iterator              list_str_iter;
    typedef std::list<Channel *>            list_ch;
    typedef list_ch::iterator               list_ch_iter;
    typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;

    std::string name;
    std::string prefix;
    int         arg_len;

    Command(std::string name);
    virtual ~Command();

    virtual void    parse_args(list_str args) = 0;
    virtual void    init_cmd() = 0;
    void            execute_command(Server* server, Client* client);

protected:
    virtual void    execute(Server* server, Client* client) = 0;
    bool            is_regi_cmd(std::string cmd);

};

#include "../Exceptions.hpp"
#include "../Reply.hpp"

#endif
