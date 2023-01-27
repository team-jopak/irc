#ifndef MODE_CMD_HPP
# define MODE_CMD_HPP

#include "../Command.hpp"

/*

사용자 이름과 채널 모두 모드를 변경할 수 있음

MODE 메시지를 구문 분석 할 때 전체 메시지를 먼저 구문 분석한 다음 그 결과로 발생한 변경 사항을 전달하는 것이 좋음

1. Command: MODE
2. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_CHANOPRIVSNEEDED
    3. ERR_NOTONCHANNEL
    4. ERR_NOSUCHNICK
    5. ERR_KEYSET
    6. ERR_NOSUCHCHANNEL
    7. ERR_UNKNOWNMODE
    8. ERR_USERSDONTMATCH
    9. ERR_UMODEUNKNOWNFLAG
    10. RPL_CHANNELMODEIS
    11. RPL_ENDOFBANLIST
    12. RPL_BANLIST
    13. RPL_UMODEIS

*/

class Mode_cmd : public Command
{
public:
    Mode_cmd() : Command("MODE")
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

    virtual void execute(Server server)
    {
        std::cout << "Execute MODE" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif