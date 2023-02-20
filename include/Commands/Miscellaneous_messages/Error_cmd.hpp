#ifndef ERROR_CMD_HPP
# define ERROR_CMD_HPP

#include "../Command.hpp"

/*

1. Command: ERROR
2. Parameters: <error message>
3. Replies
    1. None

운영자에게 심각하거나 치명적인 오류를 보고 할 때 서버에서 사용하기 위한 명령어

한 서버에서 다른 서버로 보낼 수 있지만 정상적인 등록되지 않은 클라이언트에 허용해서는 안됩니다.

ERROR 메시지는 서버 간 링크에서만 발생하는 오류를 보고하는 데 사용됩니다.

ERROR 메시지는 다른 쪽 서버(연결된 모든 운영자에게 전송)와 현재 연결된 모든 운영자에게 전송됩니다.

서버에서 수신 된 경우 다른 서버로 전송하지 않습니다.

서버가 수신 된 ERROR 메시지를 운영자에게 보낼 때 메시지는 NOTICE 메시지 내에 캡슐화되어 클라이언트가 오류에 대한 책임이 없음을 나타냅니다.

*/

class Error_cmd : public Command
{
public:
    Error_cmd() : Command("ERROR")
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
