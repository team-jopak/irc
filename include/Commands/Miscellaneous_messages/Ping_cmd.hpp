#ifndef PING_CMD_HPP
# define PING_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PING
2. Parameters: <server1> [<server2>]
3. Replies
    1. ERR_NOORIGIN
    2. ERR_NOSUCHSERVER

PING 는 연결의 다른 쪽 끝에 활성 클라이언트가 있는지 테스트 하는 데 사용함

다른 활동이 감지되지 않으면 정기적으로 PING 메시지가를 전송

연결이 설정된 시간 내에 PING 명령에 응답하지 못하면 해당 연결이 닫힘

PING 메시지를 수신하는 모든 클라이언트는 가능한 한 빨리 <server1> 에 적절한 PONG 메시지를 사용하여 응답해야 함

서버는 PING 명령에 응답하지 않아야 하지만 연결이 활성 상태임을 나타내기 위해 연결의 다른 쪽 끝의 PING 에 의존해야 함

<server2> 매개 변수가 지정되면 PING 메시지가 <server2>로 전달 됨

*/

class Ping_cmd : public Command
{
private:
    std::string _server;

public:
    Ping_cmd() : Command("PING")
    {
    }

    virtual void parse_args(list_str args)
    {
        if (args.size() != 1)
        {
            throw Err_needmoreparams("PING");
        }
        list_str_iter it = args.begin();
        _server = (*it);
    }

    // 
    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute PING" << std::endl;
        if (_server == server->get_host() || _server == server->get_name())
            client->message_client(":" + server->get_name() + " PONG " + server->get_name() + " :" + _server);
        else
            throw Err_nosuchserver(_server);
        init_cmd();
    }

    virtual void init_cmd()
    {
        _server = "";
        std::cout << "Init command" << std::endl;
    }

};

#endif
