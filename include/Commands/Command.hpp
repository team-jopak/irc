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

    Command(std::string name)
    {
        this->name = name;
    }

    virtual void parse_args(list_str args) = 0;
    virtual void init_cmd() = 0;
    void execute_command(Server* server, Client* client)
    {
        // auth
        // pass, nick, user 명령어를 사용하여 인증을 받았는지 확인
        // 만약에 받지 않았다면 에러 메세지
    

        // pass 확인
        // nick, user 확인

        if (!client->is_pass())
        {
            if (this->name != "PASS")
            {
                // error
            }
        }
        else if (!client->is_auth())
        {
            if (this->name != "NICK" && this->name != "USER")
                throw Err_451(this->name);
        }
        execute(server, client);
    }

protected:
    virtual void execute(Server* server, Client* client) = 0;

};

#include "../Exceptions.hpp"
#include "../Reply.hpp"

#endif
