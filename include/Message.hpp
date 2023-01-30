#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <list>

#include "Commands/Cmd_includes.hpp"


class Message 
{
public:
    typedef std::list<std::string>          str_list;
    typedef str_list::iterator              str_list_iter;
    typedef std::map<std::string, Command*> cmd_map;
    typedef cmd_map::iterator               cmd_map_iter;

    cmd_map commands;
    
    Message()
    {
        commands["PASS"] = new Pass_cmd();
    }

    ~Message()
    {
        // command 인스턴스 제거
    }

    Command* parse_msg(std::string msg) 
    {
        // msg 끝에는 개행이 있어야 한다.

        // 개행 제거
        _remove_nl(msg);

        str_list        splited = _split(msg, ' ');
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

private:
    bool _is_command(std::string str)
    {
        return (commands.find(str) != commands.end());
    }

    bool _is_prefix(std::string str)
    {
        return (str[0] == ':');
    }

    void _remove_nl(std::string& str)
    {
        std::string::iterator   end_iter = std::prev(str.end());
        char                    end_char = *(end_iter);

        if (end_char == '\n')
            str.erase(end_iter);
    }

    str_list _split(std::string input, char delimiter) 
    {
        str_list answer;
        std::stringstream ss(input);
        std::string temp;
    
        while (std::getline(ss, temp, delimiter)) {
            answer.push_back(temp);
        }
    
        return (answer);
    }
};

#endif
