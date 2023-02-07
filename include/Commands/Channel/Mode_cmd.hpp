#ifndef MODE_CMD_HPP
# define MODE_CMD_HPP

#include "../Command.hpp"
#include <queue>

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
s - 비밀 채널 플래그; 해당 채널에 접속한 유저만 채널이 표시됨 (whois, list 등)
i - 초대 전용 채널 플래그
t - 채널 운영자 전용, 플래그에 의해 설정 가능한 주제;
n - 외부의 클라이언트에서 채널로 보내는 메시지가 없습니다.
m - 중재 채널; creator, operator, voice 권한이 있는 유저만 메시지 전송 가능
l - 채널에 사용자 제한을 설정합니다. l <limit> or -l
b - 금지 마스크를 설정하여 사용자를 차단합니다. b <ban mask> or -b
v - 중재 채널에서 말할 수 있는 능력 제공/취득;
k - 채널 키(암호)를 설정합니다. k <key> or -k

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

- 옵션을 실행하면서 channel 또는 user 객체를 변경한다.
- 객체를 변경하는 함수는 객체의 맴버 함수이다.

*/

class Mode_cmd : public Command
{
private:
    typedef std::pair<char, bool>   pair_flag;
    typedef std::vector<pair_flag>  vec_flag;
    typedef vec_flag::iterator      vec_flag_iter;

    std::string             name;
    vec_flag                flags;
    std::queue<std::string> cmd_args;

public:
    Mode_cmd() : Command("MODE")
    {
    }

    virtual void parse_args(list_str args)
    {
        if (args.size() < 1)
        {
            // 461 :Not enough parameters.
            return ;
        }

        list_str_iter iter = args.begin();

        // nick/channel name
        name = *iter++;

        // flags
        std::string flag_str = *iter;
        int         len = flag_str.size();
        bool        is_on = true;

        for (int i=0; i<len; i++)
        {
            if (flag_str[i] == '+')
                is_on = true;
            else if (flag_str[i] == '-')
                is_on = false;
            else
                _insert_flag(flag_str[i], is_on);
        }
        iter++;

        // command args
        for (; iter!=args.end(); iter++)
        {
            this->cmd_args.push(*iter);
        }
    }

    virtual void execute(Server* server, Client* client)
    {
        if (name[0] == '#')
            _mode_ch(server, client);
        else
            _mode_usr(server, client);
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

private:
    void _insert_flag(char c, bool is_on)
    {
        vec_flag_iter iter = this->flags.begin();
        vec_flag_iter end = this->flags.end();

        for (; iter != end; iter++)
        {
            if (iter->first == c)
            {
                iter->second = is_on;
                return ;
            }
        }

        this->flags.push_back(pair_flag(c, is_on));
    }

    void _mode_usr(Server* server, Client*)
    {
        Client*         cli = server->get_client_by_nickname(name);
        vec_flag_iter   iter = this->flags.begin();
        vec_flag_iter   end = this->flags.end();
        char            flag;
        bool            is_on;

        if (cli == NULL)
        {
            // 401 :No such nick/channel
            return ;
        }

        for (; iter != end; iter++)
        {
            flag = iter->first;
            is_on = iter->second;

            if (flag == 'i' || flag == 's' || flag == 'w' || flag == 'o')
                cli->set_flag(flag, is_on);
            else
            {
                // 없는 옵션 플래그 예외 처리
            }
        }
    }
    
    void _mode_ch(Server* server, Client* client)
    {
        Channel*        ch = server->get_channel(name);
        vec_flag_iter   iter = this->flags.begin();
        vec_flag_iter   end = this->flags.end();
        char            flag;
        bool            is_on;

        if (ch == NULL)
        {
            // 403 :No such channel
            return ;
        }

        if (!ch->op->exist(client))
        {
            // 482 :You must have channel op access or above to set channel mode p
            return ;
        }

        for (; iter != end; iter++)
        {
            flag = iter->first;
            is_on = iter->second;

            if (flag == 'o')
                _mode_ch_o(ch, client, is_on);
            else if (flag == 'l')
                _mode_ch_l(ch, ft::stoi(_get_arg()));
            else if (flag == 'b')
                _mode_ch_b(ch, _get_arg());
            else if (flag == 'v')
                _mode_ch_v(ch, client, is_on);
            else if (flag == 'k')
                _mode_ch_k(ch, is_on, "");
            else if (flag == 't' || flag == 'p' || flag == 's' || flag == 'i' || flag == 'n' || flag == 'm')
                ch->set_flag(flag, is_on);
            else
            {
                // 없는 옵션 플래그 예외 처리
            }
        }
    }

    std::string _get_arg()
    {
        std::string arg = this->cmd_args.front();
        this->cmd_args.pop();
        return (arg);
    }

    // 채널 운영자 설정
    void _mode_ch_o(Channel* ch, Client* client, bool is_on)
    {
        if (is_on)
            ch->op->set(client);
        else
            ch->op->del(client);
    }

    // 채널 limit 설정
    void _mode_ch_l(Channel* ch, int limit)
    {
        if (limit == -1)
        {
            // 잘못된 limit 예외 처리
            return ;
        }
        ch->set_limit(limit);
    }
   
    // 채널 마스크 추가
    void _mode_ch_b(Channel* ch, std::string mask)
    {
        ch->add_mask(mask);
    }

    // 사용자에게 말할 수 있는 권한 제공
    void _mode_ch_v(Channel* ch, Client* client, bool is_on)
    {
        if (is_on)
            ch->voice->add(client);
        else
            ch->voice->del(client);
    }

    // 채널 암호 설정
    void _mode_ch_k(Channel* ch, bool is_on, std::string key)
    {
        ch->set_flag('k', is_on);
        ch->set_key(key);
    }
};

#endif
