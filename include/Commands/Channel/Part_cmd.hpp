#ifndef PART_CMD_HPP
# define PART_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PART
2. Parameters: <channel>{,<channel>}
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_NOTONCHANNEL
    3. ERR_NOSUCHCHANNEL

메시지를 보내는 클라이언트가 매개 변수 문자열에 나열된 모든 주어진 채널의 활성 사용자 목록에서 제거되도록 함

*/

class Part_cmd : public Command
{
public:
    Part_cmd() : Command("PART")
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
        std::cout << "Execute PART" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
