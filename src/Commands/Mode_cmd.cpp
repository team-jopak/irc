#include "../../include/Commands/Channel/Mode_cmd.hpp"

Mode_cmd::Mode_cmd() : Command("MODE")
{
}

void Mode_cmd::parse_args(list_str args)
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

void Mode_cmd::execute(Server* server, Client* client)
{
    this->server = server;
    this->client = client;
    if (is_ch_mode)
    {
        this->tar_ch = server->get_channel(name);
        _mode_ch();
    }
    else
    {
        this->tar_usr = server->get_client_by_nickname(name);
        _mode_usr();
    }
    init_cmd();
}

void Mode_cmd::init_cmd()
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

std::string Mode_cmd::_get_result_msg()
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

void Mode_cmd::_push_flag_str(std::string flag, bool is_on)
{
    if (is_on)
        this->result_flag.push_back("+" + flag);
    else
        this->result_flag.push_back("-" + flag);
}


void Mode_cmd::_throw_trash(Client* client)
{
    std::vector<char>::iterator iter = trash.begin();
    std::vector<char>::iterator end = trash.end();

    for (; iter != end; iter++)
        client->message_client(Err_472(std::string(1, *iter)).what());
}

bool Mode_cmd::_set_name(std::string name_str)
{
    this->name = name_str;
    return (this->name[0] == '#');
}

void Mode_cmd::_set_flag(std::string flag_str)
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

bool Mode_cmd::_is_flag(char c)
{
    return ((c == '+' || c == '-') || 
            (this->is_ch_mode && _is_flag_ch(c)) ||
            (!this->is_ch_mode && _is_flag_usr(c)));
}

bool Mode_cmd::_is_flag_ch(char c)
{
    char op[11] = {'o', 'p', 's', 'i', 't', 'n', 'm', 'l', 'b', 'v', 'k'};

    for (int i=0; i<11; i++)
    {
        if (op[i] == c)
            return (true);
    }
    return (false);
}

bool Mode_cmd::_is_flag_usr(char c)
{
    char op[4] = {'i', 's', 'w', 'o'};

    for (int i=0; i<4; i++)
    {
        if (op[i] == c)
            return (true);
    }
    return (false);
}

std::string Mode_cmd::_get_arg()
{
    std::string arg;

    if (this->args_iter == this->cmd_args.end())
        return ("");
    arg = *this->args_iter;
    this->args_iter++;
    return (arg);
}

void Mode_cmd::_mode_usr()
{
    std::string::iterator   iter = this->flags.begin();
    std::string::iterator   end = this->flags.end();
    char                    flag;
    bool                    is_on;

    if (this->tar_usr == NULL)
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
                if (this->tar_usr->set_flag(flag, is_on))
                    _push_flag_str(std::string(1, flag), is_on);
            }
            catch (const std::exception& e)
            {
                server->serverResponse(e.what(), this->client->get_socket_fd());
            }
        }
    }
}

void Mode_cmd::_mode_ch()
{
    std::string::iterator   iter_flag = this->flags.begin();
    std::string::iterator   end = this->flags.end();
    bool                    is_on = true;
    std::string             msg;

    if (this->tar_ch == NULL)
        throw Err_403(this->name);
    _throw_trash(this->client);
    if (iter_flag == end)
    {
        // 채널의 정보를 보내고 마침
    }
    for (; iter_flag != end; iter_flag++)
    {
        if (*iter_flag == '+')
            is_on = true;
        else if (*iter_flag == '-')
            is_on = false;
        else if (this->tar_ch->check_flag(*iter_flag) != is_on)
            _set_mode_ch(*iter_flag, is_on);
    }
    msg = _get_result_msg();
    if (msg.size() > 0)
        this->server->reply->send_channel_exec(this->tar_ch, this->client, msg);
}

void Mode_cmd::_set_mode_ch(char flag, bool is_on)
{
   try
    {
        if (flag == 'o')
            _mode_ch_o(is_on);
        else if (flag == 'l')
            _mode_ch_l(is_on);
        else if (flag == 'b')
            _mode_ch_b(is_on);
        else if (flag == 'v')
            _mode_ch_v(is_on);
        else if (flag == 'k')
            _mode_ch_k(is_on);
        else
            _mode_ch_etc(flag, is_on);
    }
    catch(const std::exception& e)
    {
        server->serverResponse(e.what(), client->get_socket_fd());
    }
}

void Mode_cmd::_mode_ch_etc(char flag, bool is_on)
{
    if ((flag == 'i' || flag == 's') && !this->tar_ch->op->exist(client))
        throw Err_482(client->get_nickname());
    if (this->tar_ch->set_flag(flag, is_on))
        _push_flag_str(std::string(1, flag), is_on);
}

// 채널 limit 설정
void Mode_cmd::_mode_ch_l(bool is_on)
{
    std::string limit_str = _get_arg();
    long        limit;

    if (limit_str.size() == 0)
        throw Err_696(this->tar_ch->get_name(), "l");
    if (!this->tar_ch->op->exist(client))
        throw Err_482(client->get_nickname());
    limit = ft::stol(limit_str);
    if (limit < 0)
        throw Err_696(this->tar_ch->get_name(), "l", limit_str);
    this->tar_ch->set_flag('l', is_on);
    this->tar_ch->set_limit(limit);
    _push_flag_str("l", is_on);
    this->result_args.push_back(limit_str);
}

// 채널 운영자 설정
void Mode_cmd::_mode_ch_o(bool is_on)
{
    std::string arg = _get_arg();
    Client*     tar;

    if (arg.size() == 0)
        throw Err_696(this->tar_ch->get_name(), "o");
    if (!this->tar_ch->op->exist(client))
        throw Err_482(client->get_nickname());
    tar = this->tar_ch->joined->get(arg);
    if (tar == NULL)
        throw Err_401(arg, true);
    if ((is_on && this->tar_ch->op->add(client)) 
        || (!is_on && this->tar_ch->op->del(client)))
    {
        _push_flag_str("o", is_on);
        this->result_args.push_back(arg);
    }
}

// 사용자에게 말할 수 있는 권한 제공
void Mode_cmd::_mode_ch_v(bool is_on)
{
    std::string arg = _get_arg();
    Client*     tar;

    if (arg.size() == 0)
        throw Err_696(this->tar_ch->get_name(), "v");
    if (!this->tar_ch->op->exist(client))
        throw Err_482(client->get_nickname());
    tar = this->tar_ch->joined->get(arg);
    if (tar == NULL)
        throw Err_401(arg, true);
    if ((is_on && this->tar_ch->voice->add(client)) 
        || (!is_on && this->tar_ch->voice->del(client)))
    {
        _push_flag_str("v", is_on);
        this->result_args.push_back(arg);
    }
}

// 채널 암호 설정
void Mode_cmd::_mode_ch_k(bool is_on)
{
    std::string key = _get_arg();

    if (key.size() == 0 && is_on)
        throw Err_696(this->tar_ch->get_name(), "k");
    if (!this->tar_ch->op->exist(client))
        throw Err_482(this->name);
    if (this->tar_ch->set_flag('k', is_on))
    {
        this->tar_ch->set_key(key);
        _push_flag_str("k", is_on);
        this->result_args.push_back(key);
    }
}

// 채널 마스크 추가
void Mode_cmd::_mode_ch_b(bool is_on)
{
    std::string mask;

    if (!this->tar_ch->op->exist(client))
        throw Err_482(client->get_nickname());
    mask = _get_arg();

    if (mask.empty())
    {
        // send ban list 


    }

    // is_on에 따라서 ban 추가 / 제거

    if (!this->tar_ch->add_mask(mask))
        throw Err_697(mask);

    // 이미 존재하는 마스크라면 에러 출력
    // :irc.local 697 aaaa #a cpak!*@* b :Channel ban list already contains cpak!*@*
}

void Mode_cmd::_send_banlist()
{
    map_client_iter iter = this->tar_ch->banned->begin();
    map_client_iter end = this->tar_ch->banned->end();

    for (; iter != end; iter++)
    {

    }
}

std::string Mode_cmd::_get_mask(std::string mask)
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