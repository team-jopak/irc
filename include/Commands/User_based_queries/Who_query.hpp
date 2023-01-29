#ifndef WHO_QUERY_HPP
# define WHO_QUERY_HPP

#include "../Command.hpp"

/*

1. Command: WHO
2. Parameters: [<name> [<o>]]
3. Replies
    1. ERR_NOSUCHSERVER
    - RPL_WHOREPLY(352)
        
        "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
        
    - RPL_ENDOFWHO(315)
        
        "<name> :End of WHO list"
        

클라이언트가 제공한 <name> 매개 변수와 '일치하는' 정보 목록을 반환하는 쿼리를 생성하기 위해 클라이언트에 사용됨

<name> 매개 변수가 없으면 표시되는 모든 사용자가 나열됨

- 보이지 않는 사용자( + i 모드) 및 요청 클라이언트와 공통 채널이 없는 사용자
- 가능한 모든 항목과 일치하는 와일드 카드를 사용하여 동일한 결과를 얻을 수 있음
- name에 0이 들어와도 동일함

WHO에 전달 된 <name> 은 <name> 채널을 찾을 수 없는 경우 사용자의 호스트, 서버, 실제 이름 및 별명과 일치하는 결과를 반환

o 매개 변수가 전달되면 결과 중에서 오퍼레이터인 결과만 반환

*/

class Who_query : public Command
{
public:
    Who_query() : Command("WHO")
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
        std::cout << "Execute WHO" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
