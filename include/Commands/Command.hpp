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

        /*

        client 등록
        - nick, user를 모두 입력하면 등록된다. 
        - pass가 있는 경우 입력해야 한다.

        - pass가 있으나 입력하지 않고 등록한다면 에러 메세지를 보내며 연결을 끊는다.
        - pass를 언제 사용하지는 중요하지 않고 등록 전에만 사용하면 된다.
        - 등록을 일정 시간 동안 하지 않는다면 연결을 끊는다.

        */

        // 등록을 하지 않고 다른 명령어를 사용하는 경우에 에러 발생
        if (!client->is_auth() && (this->name != "NICK" && this->name != "USER" && this->name != "PASS"))
            throw Err_451(this->name);
        execute(server, client);
        if (!client->is_pass())
        {
            // 에러 메세지
        }
    }

protected:
    virtual void execute(Server* server, Client* client) = 0;

};

#include "../Exceptions.hpp"
#include "../Reply.hpp"

#endif
