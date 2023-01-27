#ifndef NAMES_CMD_HPP
# define NAMES_CMD_HPP

#include "../Command.hpp"

/*

1. Command: NAMES
2. Parameters: [<channel>{,<channel>}]
3. Replies
    1. RPL_NAMREPLY
    2. RPL_ENDOFNAMES

사용자가 볼 수 있는 모든 채널에서 볼 수 있는 모든 별명을 나열

채널 이름은 비공개(+p), 비밀(+s)이 아니거나 실제로 존재하는 이름

<channel> 매개 변수는 유효한 경우 정보를 반환 할 채널을 지정

잘못된 채널 이름에 대한 오류 응답이 없음

<channel> 매개 변수가 제공되지 않으면 모든 채널 및 해당 점유자의 목록이 리턴됨

목록의 끝에는 어느 채널에도 표시되지 않은 사용자 목록이 채널 *에 있는 것으로 표시 됨

*/

class Names_cmd : public Command
{
public:
    Names_cmd() : Command("NAMES")
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
        std::cout << "Execute NAMES" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif