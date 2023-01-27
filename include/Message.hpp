#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>

#include "Commands/Cmd_includes.hpp"

class Message 
{
public:
    typedef std::vector<std::string>        str_vec;
    typedef str_vec::iterator               str_vec_iter;
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

        str_vec         result = _split(msg, ' ');
        str_vec_iter    iter = result.begin();
        str_vec_iter    end = result.end();

        Command*        cmd;

        // 첫번째 문자가 접두사인지 확인
        if (_is_prefix(*iter))
        {
            // 접두사 처리
            std::cout << "prefix : " << (*iter) << std::endl;
            ++iter;
        }

        // 명령어 확인
        if (!_is_command(*iter))
        {
            // Exception - 잘못된 명령
            std::cout << "Wrong command" << std::endl;
            return (NULL);
        }

        // 명령어 객체 지정
        cmd = commands[*iter];
        ++iter;

        // 명령어 객체에 인자 전달
        (*cmd).parse_args(iter, end);

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

    str_vec _split(std::string input, char delimiter) 
    {
        str_vec answer;
        std::stringstream ss(input);
        std::string temp;
    
        while (std::getline(ss, temp, delimiter)) {
            answer.push_back(temp);
        }
    
        return (answer);
    }
};

#endif