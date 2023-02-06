#ifndef NOTICE_CMD_HPP
# define NOTICE_CMD_HPP

#include "../Command.hpp"

/*

1. Command: NOTICE
2. Parameters: <nickname> <text>
3. Replies
    1. None

PRIVMSG와 유사하게 사용함

NOTICE에 대한 응답으로 자동 회신을 보내면 안됨

이 규칙은 서버에도 적용

알림을 받았을 때 클라이언트에게 오류 응답을 보내선 안됨

해당 규칙은 클라이언트가 수신한 내용에 대한 응답으로 자동으로 무언가를 보내는 사이의 루프를 방지하는 것

일반적으로 다른 자동화 장치와 루프가 되지 않도록 항상 응답하는 것으로 보이는 자동 장치에 의해 사용됨

*/

class Notice_cmd : public Command
{
private:
    std::list<std::string> _receiver;
    std::string _message;
    bool _wildcard;

    bool is_wildcard_exist(std::string str)
    {
        if (str.find('?') != std::string::npos)
            return true;
        if (str.find('*') != std::string::npos)
            return true;
        return false;
    }

    bool check_wildcard_validity()
    {
        bool ret = true;

        for (str_list_iter it = _receiver.begin(); it != _receiver.end(); it++)
        {
            if (*(*it).begin() == '#' || *(*it).begin() == '?')
            {
                if ((*it).find_last_of('.') != std::string::npos)
                {
                    // check wildcard exist
                    size_t pos = (*it).find_last_of('.');
                    std::string substr = (*it).substr(pos + 1);
                    ret &= !is_wildcard_exist(substr);
                }
                else
                    ret &= false;
            }
            else
            {
                // if wildcard exist false;
                ret &= !is_wildcard_exist(*it);
            }
        }
        return (ret);
    }
public:
    Notice_cmd() : Command("NOTICE")
    {
        _message = "";
        _wildcard = false;
    }

    virtual void parse_args(str_list args)
    {
        str_list_iter   it = args.begin();
        // args 수가 모자란 경우
        if (args.size() < 2)
        {
            return ;
        }
        _receiver = split((*it), ',');
        _message = (*(++it));
        // wildcard 존재여부 확인 (wildcard는 operator 권한이 있어야 사용가능)
        for (str_list_iter it_rec; it_rec != _receiver.end(); it_rec++)
        {
            if (((*it_rec).find('?') != std::string::npos) || (*it_rec).find('*') != std::string::npos)
                _wildcard = true;
        }
        if (_wildcard && !check_wildcard_validity())
            return ;
    }

    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute PRIVMSG" << std::endl;
        if (_wildcard && 0) // 1 << client.is_oper()
            return ;
        
        for (str_list_iter it = _receiver.begin(); it != _receiver.end(); it++)
        {
            if (*(*it).begin() == '#' || *(*it).begin() == '?')
            {
                ; //server or host
            }
            else
            {
                Client *dest = server->get_client_by_nickname(*it);
                if (!dest)
                    return ;
                dest->message_client(dest->get_message_prefix() + " NOTICE " + (*it) + _message);
            }
        }
        init_cmd();
    }

    virtual void init_cmd()
    {
        _message = "";
        _wildcard = false;
        _receiver.clear();
        std::cout << "Init command" << std::endl;
    }

};

#endif
