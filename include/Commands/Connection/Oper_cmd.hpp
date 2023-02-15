#ifndef OPER_CMD_HPP
# define OPER_CMD_HPP

#include "../Command.hpp"
#define OPER "42"

/*

1. Command: OPER
2. Parameters: <user> <password>
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_NOOPERHOST
    3. ERR_PASSWDMISMATCH
    4. RPL_YOUREOPER

일반 사용자가 운영자 권한을 얻는 데 사용

OPER 명령을 보내는 클라이언트가 주어진 사용자에 대해 올바른 암호를 제공하면 서버는 클라이언트 별명에 대해 "MODE +o"를 실행하여 나머지 네트워크에 새 운영자를 알림

OPER 메시지는 클라이언트-서버 전용

*/

class Oper_cmd : public Command
{
private:
    std::string _nickname;
    std::string _password;

public:
    Oper_cmd() : Command("OPER")
    {
    }

    virtual void parse_args(list_str args)
    {
        std::cout << "args : ";
        
        // 매개변수 개수 확인
        if (args.size() != 2)
        {
            throw Err_461("OPER");
        }

        list_str_iter it_args = args.begin();
        _nickname = *it_args;
        _password = *(++it_args);
    }

    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute OPER" << std::endl;

        (void)client;
        Client *c = server->get_client_by_nickname(_nickname);
        if (!c)
            throw Err_431();
        if (c->is_oper())
            throw Err_462();
        if (_password == OPER)
            c->set_oper();
        else
            throw Err_464();
        
        std::string message = ":" + client->get_message_prefix() + " You are now an IRC operator";
        client->message_client(message.c_str());

        init_cmd();
    }

    virtual void init_cmd()
    {
        _nickname = "";
        _password = "";
        std::cout << "Init command" << std::endl;
    }

};

#endif
