#ifndef TOPIC_CMD_HPP
# define TOPIC_CMD_HPP

#include "../Command.hpp"

/*

1. Command: TOPIC
2. Parameters: <channel> [<topic>]
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_NOTONCHANNEL
    3. ERR_CHANOPRIVSNEEDED
    4. RPL_NOTOPIC
    5. RPL_TOPIC

채널의 주제를 변경하거나 보는데 사용

주어진 <topic>이 없는 경우 <channel> 채널에 대한 주제가 리턴

<topic> 매개변수가 있는 경우 채널 모드에서 이 작업을 허용하면 해당 채널의 주제가 변경됨

*/

class Topic_cmd : public Command
{
public:
    Topic_cmd() : Command("TOPIC")
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
        std::cout << "Execute TOPIC" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif