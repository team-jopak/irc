#include "../include/Message.hpp"

Message::Message()
{
    // Connection
    commands["NICK"] = new Nick_cmd();
    commands["PASS"] = new Pass_cmd();
    commands["QUIT"] = new Quit_cmd();
    commands["USER"] = new User_cmd();

    // Channel
    commands["JOIN"] = new Join_cmd();
    commands["KICK"] = new Kick_cmd();
    commands["LIST"] = new List_cmd();
    commands["MODE"] = new Mode_cmd();
    commands["NAMES"] = new Names_cmd();
    commands["PART"] = new Part_cmd();
    commands["TOPIC"] = new Topic_cmd();
    commands["INVITE"] = new Invite_cmd();

    // Miscellaneous_messages
    commands["ERROR"] = new Error_cmd();
    commands["PING"] = new Ping_cmd();

    // Send_messages
    commands["NOTICE"] = new Notice_cmd();
    commands["PRIVMSG"] = new Privmsg_cmd();

    // User_based_queries
    commands["WHO"] = new Who_query();
}

Message::~Message()
{
    // Connection
    delete commands["NICK"];
    delete commands["PASS"];
    delete commands["QUIT"];
    delete commands["USER"];

    // Channel
    delete commands["JOIN"];
    delete commands["LIST"];
    delete commands["MODE"];
    delete commands["NAMES"];
    delete commands["PART"];
    delete commands["TOPIC"];
    delete commands["INVITE"];

    // Miscellaneous_messages
    delete commands["ERROR"];
    delete commands["KILL"];
    delete commands["PING"];

    // Send_messages
    delete commands["NOTICE"];
    delete commands["PRIVMSG"];

    // User_based_queries
    delete commands["WHO"];
}

// 첫번째 문자가 접두사인지 확인
// 명령어 확인
// 명령어 객체에 인자 전달
Command* Message::parse_msg(std::string msg) 
{
    list_str        splited = ft::split_list(_remove_nl(msg), ' ');
    list_str_iter   cmd_iter = splited.begin();
    std::string     prefix;
    cmd_map_iter    result;

    if (splited.size() == 0)
        throw Unknown_error();
    if (_is_prefix(*(cmd_iter)))
    {
        prefix = *(cmd_iter);
        cmd_iter++;
        splited.pop_front();
    }
    *cmd_iter = ft::str_toupper(*cmd_iter);
    if ((*cmd_iter).compare("CAP") == 0)
        throw Unknown_error();
    if ((result = commands.find(*cmd_iter)) == commands.end())
        throw Err_unknowncommand(*cmd_iter);
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
    if (str.size() != 0 && *(--end_iter) == '\r')
        str.erase(end_iter);
    return (str);
}
