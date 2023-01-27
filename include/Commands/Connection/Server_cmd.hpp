#ifndef SERVER_CMD_HPP
# define SERVER_CMD_HPP

#include "../Command.hpp"

/*

1. Command: SERVER
2. Parameters: <servername> <hopcount> <info>
3. Replies
    1. ERR_ALREADYREGISTRED

새 연결의 다른 쪽 끝이 서버임을 서버에 알리는 데 사용됩니다.

전체 네트워크를 통해 서버 데이터를 전달하는데도 사용됨

새 서버가 네트워크에 연결되면 해당 정보가 전체 네트워크에 브로드캐스트 됨

hopcount는 모든 서버가 얼마나 멀리 떨어져 있는지에 대한 내부 정보를 모든 서버에 제공하는데 사용

아직 등록되지 않았고 서버로 등록을 시도하거나 다른 서버에 대한 기존 연결에서만 수락 되어야 함

대부분의 오류는 대상 호스트에서 연결을 종료함

오류 응답은 일반적으로 숫자가 아닌 ERROR 명령을 사용하여 전송

수신 서버에 이미 알려진 서버를 도입하려고 시도하는 경우 비순환적 특성이 생기기에 연결을 끊어야 함


*/

class Server_cmd : public Command
{
public:
    Server_cmd() : Command("SERVER")
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
        (void)server;
        std::cout << "Execute SERVER" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif