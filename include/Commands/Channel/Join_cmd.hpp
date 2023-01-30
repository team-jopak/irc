#ifndef JOIN_CMD_HPP
# define JOIN_CMD_HPP

#include "../Command.hpp"

/*

1. Command: JOIN
2. Parameters: <channel>{,<channel>} [<key>{,<key>}]
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_INVITEONLYCHAN
    3. ERR_CHANNELISFULL
    4. ERR_NOSUCHCHANNEL
    5. ERR_BANNEDFROMCHAN
    6. ERR_BADCHANNELKEY
    7. ERR_BADCHANMASK
    8. ERR_TOOMANYCHANNELS
    9. RPL_TOPIC

클라이언트가 특정 채널 청취를 시작하는데 사용

클라이언트가 채널에 참여 할 수 있는지 여부는 클라이언트가 연결된 서버에서만 확인

다른 모든 서버는 사용자가 다른 서버에서 수신되면 자동으로 사용자를 채널에 추가

영향을 주는 조건은 다음과 같음

1. 채널이 초대 전용인 경우 사용자를 초대해야 함
2. 사용자의 별명/사용자 이름/호스트 이름은 활성화된 ban과 일치하지 않아야 함
3. 설정된 경우 올바른 키(암호)를 제공해야 함

사용자가 채널에 가입하면 채널에 영향을 주는 서버가 수신하는 모든 명령에 대한 알림을 받음(MODE, KICK, PART, QUIT, PRIVMSG, NOTICE 포함)

각 서버가 채널에 있는 사용자를 찾을 수 있는 위치를 알 수 있도록 모든 서버에 브로드 캐스트되어야 함

이를 통해 PRIVMSG/NOTICE 메시지를 채널에 최적으로 전달할 수 있음

JOIN이 성공하면 사용자에게 채널의 주제(RPL_TOPIC)와 채널에 있는 사용자 목록(RPL_NAMREPLY)이 전송되며 여기에는 User join이 포함

*/

class Join_cmd : public Command
{
public:
    Join_cmd() : Command("JOIN")
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
        std::cout << "Execute JOIN" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
