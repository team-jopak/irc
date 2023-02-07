#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "../Reply.hpp"
#include "../Exceptions.hpp"
#include "../util_funcs.hpp"

class Server;
class Client;

class Command
{
public:
    typedef std::list<std::string>          list_str;
    typedef list_str::iterator              list_str_iter;
    typedef std::map<std::string, Client *>	map_client;
	typedef map_client::iterator			map_client_iter;

    std::string name;
    std::string prefix;
    int         arg_len;

    Command(std::string name)
    {
        this->name = name;
    }

    // 명령어의 인자를 처리
    // Exception - 매개변수가 충분하지 않거나 잘못된 경우
    virtual void parse_args(list_str args) = 0;

    // 명령어를 실행
    // Exception - 잘못된 권한
    virtual void execute(Server* server, Client* client) = 0;

    // 클라이언트에 응답 메시지를 보낸다.
    // virtual void response() = 0;

    // 명령어 인자 초기화
    virtual void init_cmd() = 0;
};

#endif
