#ifndef WHOWAS_QUERY_HPP
# define WHOWAS_QUERY_HPP

#include "../Command.hpp"

/*

1. Command: WHOWAS
2. Parameters: <nickname> [<count> [<server>]]
3. Replies
    1. ERR_NONICKNAMEGIVEN
    2. ERR_WASNOSUCHNICK
    3. RPL_WHOWASUSER
    4. RPL_WHOISSERVER
    5. RPL_ENDOFWHOWAS

Whowas는 더 이상 존재하지 않는 별명에 대한 정보를 요청

닉네임 변경 또는 사용자가 네트워크에서 떠났을 수 있음

서버는 별칭 기록을 검색하여 어휘 적으로 동일한 별칭을 찾음(와일드카드 없음)

기록은 역방향으로 검색되며 가장 최근 항목을 먼저 반환

항목이 여러 개인 경우 최대 <count> 개의 응답이 반환

<count>가 제공되지 않은 경우 모두 반환

음수가 제공되어도 모두 반환함

*/

class Whowas_query : public Command
{
public:
    Whowas_query() : Command("WHOWAS")
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
        std::cout << "Execute WHOWAS" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
