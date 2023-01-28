#ifndef WHOIS_QUERY_HPP
# define WHOIS_QUERY_HPP

#include "../Command.hpp"

/*

1. Command: WHOIS
2. Parameters: [<server>] <nickmask>[,<nickmask>[,...]]
3. Replies
    1. ERR_NOSUCHSERVER
    2. ERR_NONICKNAMEGIVEN
    3. ERR_NOSUCHNICK
    4. RPL_WHOISUSER
    5. RPL_WHOISCHANNELS
    6. RPL_WHOISSERVER
    7. RPL_AWAY
    8. RPL_WHOISOPERATOR
    9. RPL_WHOISIDLE
    10. RPL_ENDOFWHOIS

특정 사용자에 대한 정보를 쿼리 하는 데 사용함

서버는 닉 마스크와 일치하는 각 사용자의 서로 다른 상태를 나타내는 여러 숫자 메시지로 이 메시지에 응답함(볼 수 있는 권한이 있는 경우)

<nickmask>에 와일드 카드가 없으면 볼 수 있는 해당 닉에 대한 정보가 표시

쉼표로 구분 된 목록이 제공될 수 있음

<server>의 경우 쿼리를 특정 서버로 보냄

- 로컬 서버만이 해당 정보를 알고 있고 다른 모든 정보는 모든 네트워크가 알고 있으므로 해당 사용자가 얼마나 오랫동안 Idle 상태인지 알고 싶은 경우 유용

*/

class Whois_query : public Command
{
public:
    Whois_query() : Command("WHOIS")
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
        std::cout << "Execute WHOIS" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
