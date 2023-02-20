#ifndef KILL_CMD_HPP
# define KILL_CMD_HPP

#include "../Command.hpp"

/*

1. Command: KILL
2. Parameters: <nickname> <comment>
3. Replies
    1. ERR_NOPRIVILEGES
    2. ERR_NOSUCHNICK
    3. ERR_NEEDMOREPARAMS
    4. ERR_CANTKILLSERVER

실제 연결이 있는 서버에 의해 클라이언트-서버 연결이 닫히도록 하는 데 사용됩니다.

KILL은 유효한 별명 목록에서 중복 항목을 발견 할 때 서버에서 사용되며 두 항목을 모두 제거하는 데 사용됩니다.

운영자도 사용할 수 있음

자동 재 연결 알고리즘이 있는 클라이언트는 연결 해제가 짧기 때문에 이 명령을 효과적으로 쓸모 없게 만듭니다.

그러나 데이터 흐름을 깨뜨리고 많은 양의 남용을 막는 데 사용될 수 있습니다.

어떤 사용자든 다른 사람들이 문제가 되는 시선을 유지하기 위해 생성 된 KILL 메시지를 수신하도록 선택할 수 있습니다.

동일한 닉네임으로 두 명의 사용자를 등록하려는 시도가 생기면 KILL 메시지가 전송되어 둘 다 사라지고 1이 다시 나타납니다.

comment 는 KILL의 실제 이유를 반영해야 합니다.

서버 생성 KILL의 경우 일반적으로 충돌하는 두 닉네임의 출처에 관한 세부 정보로 구성됩니다.

가짜로 KILL을 생성하는 것을 방지하기 위해 주석은 통과하는 각 서버에 의해 업데이트되는 KILL-PATH도 표시하며, 각 서버는 경로에 이름을 추가합니다.

KILL David ([csd.bu.edu](http://csd.bu.edu/) <- [tolsun.oulu.fi](http://tolsun.oulu.fi/))

*/

class Kill_cmd : public Command
{
public:
    Kill_cmd() : Command("KILL")
    {
    }

    virtual void parse_args(list_str args)
    {
        (void)args;
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        init_cmd();
    }

    virtual void init_cmd()
    {
    }

};

#endif
