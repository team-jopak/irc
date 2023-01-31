#ifndef LIST_CMD_HPP
# define LIST_CMD_HPP

#include "../Command.hpp"

/*

1. Command: LIST
2. Parameters: [<channel>{,<channel>} [<server>]]
3. Replies
    1. ERR_NOSUCHSERVER
    2. RPL_LIST
    3. RPL_LISTSTART
    4. RPL_LISTEND

채널과 주제를 나열하는 데 사용됨

<channel> 매개 변수를 사용하면 해당 채널의 상태만 표시됨

쿼리를 생성하는 클라이언트가 실제로 해당 채널에 있지 않는 한 개인 채널은 주제 없이 채널 "Prv"로 나열

클라이언트가 해당 채널의 구성원이 아니면 비밀 채널이 전혀 나열되지 않음

*/

class List_cmd : public Command
{
public:
    List_cmd() : Command("LIST")
    {
    }

    virtual void parse_args(str_list args)
    {
        std::cout << "args : ";

        (void)args;
    }

    virtual void execute(Server* server, Client* client)
    {
        server->get_password();
        (void)client;
        std::cout << "Execute LIST" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
