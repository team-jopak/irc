#ifndef PRIVMSG_CMD_HPP
# define PRIVMSG_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PRIVMSG
2. Parameters: <receiver>{,<receiver>} <text to be send>
3. Replies
    1. ERR_NORECIPIENT
    2. ERR_NOTEXTTOSEND
    3. ERR_CANNOTSENDTOCHAN
    4. ERR_NOTOPLEVEL
    5. ERR_NOSUCHNICK
    6. ERR_TOOMANYTARGETS
    7. RPL_AWAY

사용자 간 개인 메시지를 보내는 데 사용

receiver는 쉼표로 구분 된 닉네임이나 채널 이름

서버/호스트 마스크일 수도 있음(운영자만 사용 가능)

이 경우 마스크와 일치하는 서버 또는 호스트가 있는 사람에게만 메시지를 전송

마스크에는 .이 하나 이상 있어야 함

그리고 마지막 .뒤에는 와일드 카드가 없음

해당 요구사항은 모든 사람들에게 메시지를 보내는 것을 방지하기 위함

와일드 카드는 ?, /, *

*/

class Privmsg_cmd : public Command
{
public:
    Privmsg_cmd() : Command("PRIVMSG")
    {
    }

    virtual void parse_args(str_list args)
    {
        std::cout << "args : ";

        (void)args;
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        std::cout << "Execute PRIVMSG" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
