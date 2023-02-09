#ifndef PRIVMSG_CMD_HPP
# define PRIVMSG_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PRIVMSG
2. Parameters: <receiver>{,<receiver>} <text to be send>
3. Replies
    1. ERR_NORECIPIENT
    2. ERR_NOTEXTTOSEND
    3. ERR_CANNOTSENDTOCHAN
    4. ERR_NOTOPLEVEL
    5. ERR_NOSUCHNICK
    6. ERR_TOOMANYTARGETS
    7. RPL_AWAY

사용자 간 개인 메시지를 보내는 데 사용

receiver는 쉼표로 구분 된 닉네임이나 채널 이름 (only comma, no space)

서버/호스트 마스크일 수도 있음(운영자만 사용 가능)

이 경우 마스크와 일치하는 서버 또는 호스트가 있는 사람에게만 메시지를 전송

마스크에는 .이 하나 이상 있어야 함

그리고 마지막 .뒤에는 와일드 카드가 없음

해당 요구사항은 모든 사람들에게 메시지를 보내는 것을 방지하기 위함

와일드 카드는 ?, /, *

*/

class Privmsg_cmd : public Command
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

        for (list_str_iter it = _receiver.begin(); it != _receiver.end(); it++)
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
    Privmsg_cmd() : Command("PRIVMSG")
    {
        _message = "";
        _wildcard = false;
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   it = args.begin();
        // args 수가 모자란 경우
        if (args.size() < 2)
        {
            return ;
        }
        _receiver = ft::split((*it), ',');
        _message = (*(++it));
        // wildcard 존재여부 확인 (wildcard는 operator 권한이 있어야 사용가능)
        for (list_str_iter it_rec; it_rec != _receiver.end(); it_rec++)
        {
            if (((*it_rec).find('?') != std::string::npos) || (*it_rec).find('*') != std::string::npos)
                _wildcard = true;
        }
        if (_wildcard && !check_wildcard_validity())
            return ;   // wildcard 예외 메시지
    }

    virtual void execute(Server* server, Client*)
    {
        std::cout << "Execute PRIVMSG" << std::endl;
        if (_wildcard && 0) // 1 << client.is_oper()
            return ;  // no permission err msg
        
        for (list_str_iter it = _receiver.begin(); it != _receiver.end(); it++)
        {
            if (*(*it).begin() == '#')
            {
                if (_wildcard)
                {
                    Server::list_ch chlist = server->get_channel_list();
                    for (Server::list_ch::iterator it_ch = chlist.begin(); it_ch != chlist.end(); it_ch++)
                    {
                        if (ft::strmatch((*it), (*it_ch)->get_name))
                            (*it_ch)->message_channel_with_prefix(" PRIVMSG " + (*it) + _message);
                    }
                }
                else
                {
                    Channel *dest = server->get_channel(*it);
                    if (!dest)
                        return ; // err_msg;
                    dest->message_channel_with_prefix(" PRIVMSG " + (*it) + _message);
                }
            } 
            else if (*(*it).begin() == '?')
            {
                ; //server or host
            }
            else
            {
                if (_wildcard)
                {
                    Server::list_client cl_list = server->get_clients();
                    for (Server::list_client::iterator it_cl = cl_list.begin(); it_cl != cl_list.end(); it_cl++)
                    {
                        if (ft::strmatch((*it), (*it_cl)->get_nickname()))
                            (*it_cl)->message_client((*it_cl)->get_message_prefix() + " PRIVMSG " + (*it) + _message)
                    }
                }
                else
                {
                    Client *dest = server->get_client_by_nickname(*it);
                    if (!dest)
                        return ; // no such client
                    dest->message_client(dest->get_message_prefix() + " PRIVMSG " + (*it) + _message);
                }
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
