#ifndef PASS_CMD_HPP
# define PASS_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PASS
2. Parameter: <password>
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_ALREADYREGISTRED

연결 암호 설정

연결 등록(NICK/USER/SERVER)를 시도하기 전에 암호를 설정할 수 있음

등록 이전에 여러 PASS를 보낼 수 있지만 마지막으로 보낸 명령만 확인에 사용되며 등록된 이후에는 변경할 수 없습니다

*/

class Pass_cmd : public Command
{
private:
    std::string _password;


public:
    Pass_cmd() : Command("PASS")
    {
    }


    virtual void parse_args(str_list args)
    {
        std::cout << "args : ";

        (void)args;
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
