#include "../include/Message.hpp"

Message::Message()
{
    // Connection
    commands["NICK"] = new Nick_cmd();
    commands["OPER"] = new Oper_cmd();
    commands["PASS"] = new Pass_cmd();
    commands["QUIT"] = new Quit_cmd();
    commands["USER"] = new User_cmd();

    // Channel
    commands["JOIN"] = new Join_cmd();
    commands["LIST"] = new List_cmd();
    commands["MODE"] = new Mode_cmd();
    commands["NAMES"] = new Names_cmd();
    commands["PART"] = new Part_cmd();
    commands["TOPIC"] = new Topic_cmd();

    // Miscellaneous_messages
    commands["ERROR"] = new Error_cmd();
    commands["KILL"] = new Kill_cmd();
    commands["PING"] = new Ping_cmd();
    commands["PONG"] = new Pong_cmd();

    // Send_messages
    commands["NOTICE"] = new Notice_cmd();
    commands["PRIVMSG"] = new Privmsg_cmd();

    // User_based_queries
    commands["WHO"] = new Who_query();
    commands["WHOIS"] = new Whois_query();
    commands["WHOWAS"] = new Whowas_query();
}

Message::~Message()
{
    // command 인스턴스 제거
}

Command* Message::parse_msg(std::string msg) 
{
    list_str        splited = ft::split_list(_remove_nl(msg), ' ');
    list_str_iter   cmd_iter = splited.begin();
    std::string     prefix;
    cmd_map_iter    result;

    // 첫번째 문자가 접두사인지 확인
    if (_is_prefix(*(cmd_iter)))
    {
        prefix = *(cmd_iter);

        // 접두사 처리
        std::cout << "prefix : " << prefix << std::endl;
        cmd_iter++;
        splited.pop_front();
    }

    // 명령어 확인
    *cmd_iter = ft::str_toupper(*cmd_iter);
    if ((result = commands.find(*cmd_iter)) == commands.end())
        throw Err_421(*cmd_iter);

    // 명령어 객체에 인자 전달
    splited.pop_front();
    result->second->parse_args(splited);

    return (result->second);
}

bool Message::_is_command(std::string str)
{
    return (commands.find(str) != commands.end());
}

bool Message::_is_prefix(std::string str)
{
    return (str[0] == ':');
}

std::string Message::_remove_nl(std::string str)
{
    std::string::iterator   end_iter = std::prev(str.end());
    char                    end_char = *(end_iter);

    if (end_char == '\n')
        str.erase(end_iter);
    return (str);
}