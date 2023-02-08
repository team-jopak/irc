#include "../include/Message.hpp"

Message::Message()
{
    commands["NICK"] = new Nick_cmd();
    commands["OPER"] = new Oper_cmd();
    commands["PASS"] = new Pass_cmd();
    commands["QUIT"] = new Quit_cmd();
    commands["USER"] = new User_cmd();
    commands["JOIN"] = new Join_cmd();
}

Message::~Message()
{
    // command 인스턴스 제거
}

Command* Message::parse_msg(std::string msg) 
{
    // msg 끝에는 개행이 있어야 한다.

    // 개행 제거
    _remove_nl(msg);

    list_str        splited = ft::split(msg, ' ');
    std::string     prefix;

    Command*        cmd;

    // 첫번째 문자가 접두사인지 확인
    if (_is_prefix(*(splited.begin())))
    {
        prefix = *(splited.begin());
        splited.pop_front();

        // 접두사 처리
        std::cout << "prefix : " << prefix << std::endl;
    }


    // 명령어 확인
    if (!_is_command(*(splited.begin())))
    {
        // Exception - 잘못된 명령
        std::cout << "Wrong command" << std::endl;
        return (NULL);
    }

    // 명령어 객체 지정
    cmd = commands[*(splited.begin())];
    splited.pop_front();

    // 명령어 객체에 인자 전달
    (*cmd).parse_args(splited);

    return (cmd);
}

bool Message::_is_command(std::string str)
{
    return (commands.find(str) != commands.end());
}

bool Message::_is_prefix(std::string str)
{
    return (str[0] == ':');
}

void Message::_remove_nl(std::string& str)
{
    std::string::iterator   end_iter = std::prev(str.end());
    char                    end_char = *(end_iter);

    if (end_char == '\n')
        str.erase(end_iter);
}