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

    bool            is_ch_mode;
    std::string     name;
    std::string     flags;
    std::string     trash;
    vec_str         cmd_args;
    vec_str_iter    args_iter;
    vec_str         result_flag;
    vec_str         result_args;

public:
    Mode_cmd() : Command("MODE")
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter iter = args.begin();
        list_str_iter end = args.end();

        if (iter == end)
            throw Err_461("MODE");
        this->is_ch_mode = _set_name(*iter++);
        if (iter == end)
            return ;
        _set_flag(*iter++);
        cmd_args.insert(cmd_args.begin(), iter, args.end());
        args_iter = cmd_args.begin();
    }

    virtual void execute(Server* server, Client* client)
    {
        if (is_ch_mode)
            _mode_ch(server, client);
        else
            _mode_usr(server, client);
        init_cmd();
    }

    virtual void init_cmd()
    {
        is_ch_mode = false;
        name = "";
        flags = "";
        trash = "";
        result_flag.clear();
        result_args.clear();
        cmd_args.clear();
        args_iter = cmd_args.begin();
    }

private:
    std::string _get_result_msg()
    {
        std::string     flag_str;
        std::string     arg_str;
        
        if (this->result_flag.size() == 0)
            return ("");
        {
            vec_str_iter    iter = this->result_flag.begin();
            vec_str_iter    end = this->result_flag.end();
            char            sign = '+';

            for (; iter != end; iter++)
            {
                if (iter == this->result_flag.begin())
                    flag_str.append(*iter);
                else
                {
                    if ((*iter)[0] == sign)
                        flag_str.push_back((*iter)[1]);
                    else
                    {
                        flag_str.append(*iter);
                        sign = (*iter)[0];
                    }
                }
            }
        }
        {
            vec_str_iter    end = this->result_args.end();
            if (end != this->result_args.begin())
            {
                end--;
                *end = ":" + *end;
                arg_str = ft::vec_str_join(this->result_args, " ");
            }
        }
        return ("MODE " + name + " " + flag_str + " " + arg_str);
    }

    void _push_flag_str(std::string flag, bool is_on)
    {
        if (is_on)
            this->result_flag.push_back("+" + flag);
        else
            this->result_flag.push_back("-" + flag);
    }


    void _throw_trash(Client* client)
    {
        std::vector<char>::iterator iter = trash.begin();
        std::vector<char>::iterator end = trash.end();

        for (; iter != end; iter++)
            client->message_client(Err_472(std::string(1, *iter)).what());
    }

    bool _set_name(std::string name_str)
    {
        this->name = name_str;
        return (this->name[0] == '#');
    }

    void _set_flag(std::string flag_str)
    {
        int     len = flag_str.size();
        char    c;

        for (int i=0; i<len; i++)
        {
            c = flag_str[i];
            if (_is_flag(c))
                this->flags.push_back(c);
            else
                this->trash.push_back(c);
        }
    }

    bool _is_flag(char c)
    {
        return ((c == '+' || c == '-') || 
                (this->is_ch_mode && _is_flag_ch(c)) ||
                (!this->is_ch_mode && _is_flag_usr(c)));
    }

    bool _is_flag_ch(char c)
    {
        char op[11] = {'o', 'p', 's', 'i', 't', 'n', 'm', 'l', 'b', 'v', 'k'};

        for (int i=0; i<11; i++)
        {
            if (op[i] == c)
                return (true);
        }
        return (false);
    }

    bool _is_flag_usr(char c)
    {
        char op[4] = {'i', 's', 'w', 'o'};

        for (int i=0; i<4; i++)
        {
            if (op[i] == c)
                return (true);
        }
        return (false);
    }

    std::string _get_arg()
    {
        std::string arg;

        if (this->args_iter == this->cmd_args.end())
            return ("");
        arg = *this->args_iter;
        this->args_iter++;
        return (arg);
    }

    void _mode_usr(Server* server, Client* client)
    {
        Client*                 cli = server->get_client_by_nickname(this->name);
        std::string::iterator   iter = this->flags.begin();
        std::string::iterator   end = this->flags.end();
        char                    flag;
        bool                    is_on;

        if (cli == NULL)
            throw Err_401(this->name, true);
        _throw_trash(client);
        for (; iter != end; iter++)
        {
            flag = *iter;

            if (flag == '+')
                is_on = true;
            else if (flag == '-')
                is_on = false;
            else
            {
                try
                {
                    if (cli->set_flag(flag, is_on))
                        _push_flag_str(std::string(1, flag), is_on);
                }
                catch (const std::exception& e)
                {
                    server->serverResponse(e.what(), client->get_socket_fd());
                }
            }
        }
    }
    
    void _mode_ch(Server* server, Client* client)
    {
        Channel*                ch = server->get_channel(name);
        std::string::iterator   iter = this->flags.begin();
        std::string::iterator   end = this->flags.end();
        char                    flag;
        bool                    is_on = true;

        if (ch == NULL)
            throw Err_403(this->name);
        _throw_trash(client);

        if (iter == end)
        {
            // 채널의 정보를 보내고 마침

        }
        for (; iter != end; iter++)
        {
            flag = *iter;

            if (flag == '+')
                is_on = true;
            else if (flag == '-')
                is_on = false;
            else if (ch->check_flag(flag) != is_on)
            {
                try
                {
                    _set_mode_ch(ch, client, *iter, is_on);
                }
                catch(const std::exception& e)
                {
                    server->serverResponse(e.what(), client->get_socket_fd());
                }
            }
        }
        std::string msg = _get_result_msg();
        if (msg.size() > 0)
            server->reply->send_channel_exec(ch, client, msg);
    }

    void _set_mode_ch(Channel* ch, Client* client, char flag, bool is_on)
    {
        if (flag == 'o')
            _mode_ch_o(ch, client, is_on);
        else if (flag == 'l')
            _mode_ch_l(ch, client, is_on);
        else if (flag == 'b')
            _mode_ch_b(ch, client);
        else if (flag == 'v')
            _mode_ch_v(ch, client, is_on);
        else if (flag == 'k')
            _mode_ch_k(ch, client, is_on);
        else
            _mode_ch_etc(ch, client, flag, is_on);
    }

    void _mode_ch_etc(Channel* ch, Client* client, char flag, bool is_on)
    {
        if ((flag == 'i' || flag == 's') && !ch->op->exist(client))
            throw Err_482(client->get_nickname());
        if (ch->set_flag(flag, is_on))
            _push_flag_str(std::string(1, flag), is_on);
    }

    // 채널 limit 설정
    void _mode_ch_l(Channel* ch, Client* client, bool is_on)
    {
        std::string limit_str = _get_arg();
        long        limit;

        if (limit_str.size() == 0)
            throw Err_696(ch->get_name(), "l");
        if (!ch->op->exist(client))
            throw Err_482(client->get_nickname());
        limit = ft::stol(limit_str);
        if (limit < 0)
            throw Err_696(ch->get_name(), "l", limit_str);
        ch->set_flag('l', is_on);
        ch->set_limit(limit);
        _push_flag_str("l", is_on);
        this->result_args.push_back(limit_str);
    }

    // 채널 운영자 설정
    void _mode_ch_o(Channel* ch, Client* client, bool is_on)
    {
        std::string arg = _get_arg();
        Client*     tar;

        if (arg.size() == 0)
            throw Err_696(ch->get_name(), "o");
        if (!ch->op->exist(client))
            throw Err_482(client->get_nickname());
        tar = ch->joined->get(arg);
        if (tar == NULL)
            throw Err_401(arg, true);
        if ((is_on && ch->op->add(client)) 
            || (!is_on && ch->op->del(client)))
        {
            _push_flag_str("o", is_on);
            this->result_args.push_back(arg);
        }
    }

    // 사용자에게 말할 수 있는 권한 제공
    void _mode_ch_v(Channel* ch, Client* client, bool is_on)
    {
        std::string arg = _get_arg();
        Client*     tar;

        if (arg.size() == 0)
            throw Err_696(ch->get_name(), "v");
        if (!ch->op->exist(client))
            throw Err_482(client->get_nickname());
        tar = ch->joined->get(arg);
        if (tar == NULL)
            throw Err_401(arg, true);
        if ((is_on && ch->voice->add(client)) 
            || (!is_on && ch->voice->del(client)))
        {
            _push_flag_str("v", is_on);
            this->result_args.push_back(arg);
        }
    }

    // 채널 암호 설정
    void _mode_ch_k(Channel* ch, Client* client, bool is_on)
    {
        std::string key = _get_arg();

        if (key.size() == 0 && is_on)
            throw Err_696(ch->get_name(), "k");
        if (!ch->op->exist(client))
            throw Err_482(this->name);
        if (ch->set_flag('k', is_on))
        {
            ch->set_key(key);
            _push_flag_str("k", is_on);
            this->result_args.push_back(key);
        }
    }

    // 채널 마스크 추가
    void _mode_ch_b(Channel* ch, Client* client)
    {
        std::string mask;

        if (!ch->op->exist(client))
            throw Err_482(client->get_nickname());
        mask = _get_arg();

        if (mask.empty())
        {
            // send ban list 


        }


        if (!ch->add_mask(mask))
            throw Err_697(mask);

        // 이미 존재하는 마스크라면 에러 출력
        // :irc.local 697 aaaa #a cpak!*@* b :Channel ban list already contains cpak!*@*
    }

    std::string _get_mask(std::string mask)
    {

        std::list<std::string> nickname = ft::split(mask, '!');
        std::cout << nickname.size() << std::endl;

        std::string str = nickname.back();
        std::list<std::string> username = ft::split(str, '@');


        // std::string result;
        // result += nickname.size() == 0 ? "*" : nickname;
        // result += username.size() == 0 ? "*" : username;
        // result += hostname.size() == 0 ? "*" : hostname;
        return ("");
    }
};

#endif
