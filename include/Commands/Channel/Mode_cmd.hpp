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


옵션을 적용하며 적용된 문자열을 모아서 마지막에 client로 보낸다.

MODE #asdf +p-aasaanaaataaa+s
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:irc.local 472 cpak__ a :is not a recognised channel mode.
:cpak__!root@127.0.0.1 MODE #asdf :+p-nt+s

- 인자가 필요한 플래그에서 출력하는 에러 메세지
:irc.local 696 cpak #asdf l * :You must specify a parameter for the limit mode. Syntax: <limit>.
:irc.local 696 cpak #asdf k * :You must specify a parameter for the key mode. Syntax: <key>.

:irc.local 461 aaa MODE :Not enough parameters.


- 옵션없이 명령어를 사용하면 채널 정보를 띄워준다.


127.000.000.001.60288-127.000.000.001.06667: MODE #a

127.000.000.001.06667-127.000.000.001.60288: :irc.local 324 cpak #a +lnpt :1234
:irc.local 329 cpak #a :1676263198


127.000.000.001.60288-127.000.000.001.06667: MODE #a +b

127.000.000.001.06667-127.000.000.001.60288: :irc.local 368 cpak #a :End of channel ban list


- 이미 플래그가 적용되어 있다면 응답 메세지에서 제외된다.

127.000.000.001.60288-127.000.000.001.06667: MODE #a +l 1234

127.000.000.001.06667-127.000.000.001.60288: :cpak!root@127.0.0.1 MODE #a +l :1234

127.000.000.001.60288-127.000.000.001.06667: MODE #a +lp 1234

127.000.000.001.06667-127.000.000.001.60288: :cpak!root@127.0.0.1 MODE #a :+p


- 입력되는 플래그의 인자에 따라서 응답 메세지 형식이 달라진다.
- 마지막 인자에만 : 가 붙는다.

127.000.000.001.60288-127.000.000.001.06667: MODE #a -k 1234

127.000.000.001.06667-127.000.000.001.60288: :cpak!root@127.0.0.1 MODE #a -k :1234

127.000.000.001.60288-127.000.000.001.06667: MODE #a +isplk 1234 asdfawe

127.000.000.001.06667-127.000.000.001.60288: :cpak!root@127.0.0.1 MODE #a +isplk 1234 :asdfawe



MODE #a +o awef

127.000.000.001.06667-127.000.000.001.55762: :irc.local 401 aaaa awef :No such nick


*/

class Mode_cmd : public Command
{
private:
    typedef std::pair<char, bool>       pair_flag;
    typedef std::vector<pair_flag>      vec_flag;
    typedef vec_flag::iterator          vec_flag_iter;
    typedef std::vector<std::string>    vec_str;
    typedef vec_str::iterator           vec_str_iter;

    Server*         server;
    Client*         client;
    Channel*        tar_ch;
    Client*         tar_usr;
    bool            is_ch_mode;

    std::string     name;
    std::string     flags;
    std::string     trash;
    vec_str         cmd_args;
    vec_str_iter    args_iter;
    vec_str         result_flag;
    vec_str         result_args;

public:
    Mode_cmd();

    virtual void    parse_args(list_str args);
    virtual void    execute(Server* server, Client* client);
    virtual void    init_cmd();

private:
    std::string     _get_result_msg();
    void            _throw_trash(Client* client);
    void            _push_flag_str(std::string flag, bool is_on);

    bool            _is_flag(char c);
    bool            _is_flag_ch(char c);
    bool            _is_flag_usr(char c);

    bool            _set_name(std::string name_str);
    void            _set_flag(std::string flag_str);

    std::string     _get_arg();
    std::string     _get_mask(std::string mask);

    void            _send_banlist();

    void            _mode_ch();
    void            _mode_usr();

    void            _set_mode_ch(char flag, bool is_on);
    void            _mode_ch_b(bool is_on);
    void            _mode_ch_l(bool is_on);
    void            _mode_ch_o(bool is_on);
    void            _mode_ch_v(bool is_on);
    void            _mode_ch_k(bool is_on);
    void            _mode_ch_etc(char flag, bool is_on);
};

#endif
