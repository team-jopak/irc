#ifndef MODE_CMD_HPP
# define MODE_CMD_HPP

#include "../Command.hpp"

/*

MODE 명령은 이중 목적 명령으로 사용자 이름과 채널의 모드를 변경할 수 있다. 
MODE 메시지를 구문 분석 할 때 전체 메시지를 먼저 구문 분석한 다음 그 결과로 발생한 변경 사항을 전달하는 것이 좋음

1. Command: MODE
2. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_CHANOPRIVSNEEDED
    3. ERR_NOTONCHANNEL
    4. ERR_NOSUCHNICK
    5. ERR_KEYSET
    6. ERR_NOSUCHCHANNEL
    7. ERR_UNKNOWNMODE
    8. ERR_USERSDONTMATCH
    9. ERR_UMODEUNKNOWNFLAG
    10. RPL_CHANNELMODEIS
    11. RPL_ENDOFBANLIST
    12. RPL_BANLIST
    13. RPL_UMODEIS


Channel modes

Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]

모드는 채널의 op를 가져야 변경할 수 있다.

o - 채널 운영자 권한 부여/취득;
p - 개인 채널 플래그;
s - 비밀 채널 플래그;
i - 초대 전용 채널 플래그
t - 채널 운영자 전용 플래그에 의해 설정 가능한 주제;
n - 외부의 클라이언트에서 채널로 보내는 메시지가 없습니다.
m - 중재 채널;
l - 채널에 사용자 제한을 설정합니다.
b - 금지 마스크를 설정하여 사용자를 차단합니다.
v - 중재 채널에서 말할 수 있는 능력 제공/취득;
k - 채널 키(암호)를 설정합니다.

- 만약에 인자를 받지 못한 옵션이 있더라도 다른 옵션들은 설정된다.
- 옵션은 '-'와 '+'가 연속으로 들어올 수 있다.
- 플래그로 on, off 한다.
- 갍은 플래그가 -, +에 들어온다면 마지막 플래그를 적용한다.
- 연산자가 없다면 +로 간주한다.

User modes

Parameters: <nickname> {[+|-]|i|w|s|o}

사용자 모드는 일반적으로 클라이언트는 다른 사람에게 표시되거나 클라이언트가 보낸 '추가' 메시지가 무엇인지 알 수 있습니다. 
사용자 모드 명령은 보낸 사람이 둘 다인 경우에만 수락될 수 있습니다. 
메시지와 매개변수로 주어진 닉네임은 모두 동일합니다.


i - 사용자를 보이지 않는 것으로 표시합니다. 
s - 서버 알림 수신을 위해 사용자를 표시합니다. 
w - 사용자가 월롭을 받습니다. 
o - 운영자 플래그. 


// nick/channel 이름만 있는 경우에 정보를 보낸다.
// channel : 채널 정보를 보낸다.
// user : 유저 정보를 보낸다.

*/

class Mode_cmd : public Command
{
private:
    std::string                 name;
    std::map<char, bool>        flags;
    std::vector<std::string>    cmd_args;

public:
    Mode_cmd() : Command("MODE")
    {
    }

    bool is_option(char c)
    {
        char op[9] = {'o', 'p', 's', 'i', 't', 'n', 'b', 'v', 'w'};

        for (int i=0; i<9; i++)
        {
            if (op[i] == c)
                return (true);
        }
        return (false);
    }

    virtual void parse_args(str_list args)
    {
        if (args.size() < 1)
        {
            // 461 aaa MODE :Not enough parameters.
            return ;
        }

        str_list_iter iter = args.begin();

        // nick/channel 문자 처리
        name = *iter++;

        // flag 문자 처리
        std::string flag_str = *iter;
        int         len = flag_str.size();
        bool        is_on = true;

        for (int i=0; i<len; i++)
        {
            if (flag_str[i] == '+')
                is_on = true;
            else if (flag_str[i] != '-')
                is_on = false;
            else if (is_option(flag_str[i]))
                flags.insert(std::pair<char, bool>(flag_str[i], is_on));
        }
        iter++;

        // 나머지는 인자 문자 처리
        for (; iter!=args.end(); iter++)
        {
            cmd_args.push_back(*iter);
        }
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        std::cout << "Execute MODE" << std::endl;

        // channel인지 user인지 확인

        // channel 확인
        Channel* ch = server->get_channel(name);
        if (ch == NULL)
        {
            // 403 :No such channel
            return ;
        }

        // op 확인
        if (!ch->check_op_client(client))
        {
            // 482 :You must have channel op access or above to set channel mode p
            return ;
        }

        // 옵션 설정

        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
