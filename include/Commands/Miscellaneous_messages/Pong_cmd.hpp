#ifndef PONG_CMD_HPP
# define PONG_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PONG
2. Parameters: <daemon> [<daemon2>]
3. Replies
    1. ERR_NOORIGIN
    2. ERR_NOSUCHSERVER

PONG 메시지는 PING 메시지에 대한 응답

<daemon2> 가 제공되면 이 메시지는 주어진 데몬으로 전달되어야 함

<daemon> 매개 변수는 PING 메시지에 응답하고 이 메시지를 생성한 데몬의 이름

*/

class Pong_cmd : public Command
{
public:
    Pong_cmd() : Command("PONG")
    {
    }

    virtual void parse_args(list_str args)
    {
        (void)args;
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        init_cmd();
    }

    virtual void init_cmd()
    {
    }

};

#endif
