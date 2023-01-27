#ifndef NICK_CMD_HPP
# define NICK_CMD_HPP

#include "../Command.hpp"

/*

1. Command: NICK
2. Parameters: <nickname> [ <hopcount> ]
3. Replies
    1. ERR_NONICKNAMEGIVEN
    2. ERR_NICKNAMEINUSE
    3. ERR_ERRONEUSNICKNAME
    4. ERR_NICKCOLLISION

사용자에게 별명을 부여하거나 이전 별명을 변경

hopcount는 해당 유저가 홈 서버에서 얼마나 멀리 떨어져 있는지 표시하기 위해 서버에서만 사용

로컬 연결인 경우 홉은 0

클라이언트가 hopcount를 설정한 경우는 무시함

직접 연결된 클라이언트로부터 동일한 NICK을 수신한 경우에는 로컬 클라이언트에 ERR_NICKCOLLISION을 발행하고 NICK 명령을 삭제하고 킬을 생성하지 않을 수 있음

*/

class Nick_cmd : public Command
{
public:
    Nick_cmd() : Command("NICK")
    {
    }

    virtual void parse_args(str_vec_iter begin, str_vec_iter end)
    {
        std::cout << "args : ";

        for (; begin != end; begin++)
        {
            std::cout << *begin << " ";
        }
        std::cout << "\n";
    }

    virtual void execute(Server* server)
    {
        (void)server;
        std::cout << "Execute NICK" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif