#ifndef NOTICE_CMD_HPP
# define NOTICE_CMD_HPP

#include "../Command.hpp"

/*

1. Command: NOTICE
2. Parameters: <nickname> <text>
3. Replies
    1. None

PRIVMSG와 유사하게 사용함

NOTICE에 대한 응답으로 자동 회신을 보내면 안됨

이 규칙은 서버에도 적용

알림을 받았을 때 클라이언트에게 오류 응답을 보내선 안됨

해당 규칙은 클라이언트가 수신한 내용에 대한 응답으로 자동으로 무언가를 보내는 사이의 루프를 방지하는 것

일반적으로 다른 자동화 장치와 루프가 되지 않도록 항상 응답하는 것으로 보이는 자동 장치에 의해 사용됨

*/

class Notice_cmd : public Command
{
public:
    Notice_cmd() : Command("NOTICE")
    {
    }

    virtual void parse_args(list_str args)
    {
        std::cout << "args : ";

        (void)args;
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        std::cout << "Execute NOTICE" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
