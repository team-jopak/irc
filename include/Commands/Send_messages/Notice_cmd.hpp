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

public:
    Notice_cmd() : Command("NOTICE")
    {
        _message = "";
        _wildcard = false;
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   it = args.begin();
        // args 수가 모자란 경우
        if (args.size() < 2)
            throw Err_461("NOTICE");
        _receiver = ft::split((*it), ',');
        _message = (*(++it));
        // wildcard 존재여부 확인 (wildcard는 operator 권한이 있어야 사용가능)
        for (list_str_iter it_rec = _receiver.begin(); it_rec != _receiver.end(); it_rec++)
        {
            if (((*it_rec).find('?') != std::string::npos) || (*it_rec).find('*') != std::string::npos)
                _wildcard = true;
        }
        if (!_message.size())
            throw Err_412();
    }

    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute PRIVMSG" << std::endl;
        if (_wildcard && !client->is_oper())
            throw Err_481();
        
        for (list_str_iter it = _receiver.begin(); it != _receiver.end(); it++)
        {
            if (*(*it).begin() == '#')
            {
                if (_wildcard)
                {
                    Server::list_ch chlist = server->get_channel_list();
                    for (Server::list_ch::iterator it_ch = chlist.begin(); it_ch != chlist.end(); it_ch++)
                    {
                        if (ft::strmatch((*it), (*it_ch)->get_name()))
                        {
                            if (!(*it_ch)->is_talkable(client))
                                throw Err_404((*it_ch)->get_name());
                            (*it_ch)->message_channel(client->get_message_prefix() + " NOTICE " + (*it) + " "  + _message);
                        }
                    }
                }
                else
                {
                    Channel *dest = server->get_channel(*it);
                    if (!dest)
                        throw Err_401(*it);
                    if (!dest->is_talkable(client))
                        throw Err_404(dest->get_name());
                    dest->message_channel(client->get_message_prefix() + " NOTICE " + (*it) + " " + _message);
                }
            }
            else
            {
                if (_wildcard)
                {
                    Server::list_client cl_list = server->get_clients();
                    for (Server::list_client::iterator it_cl = cl_list.begin(); it_cl != cl_list.end(); it_cl++)
                    {
                        if (ft::strmatch((*it), (*it_cl)->get_nickname()))
                            (*it_cl)->message_client(client->get_message_prefix() + " NOTICE " + (*it) + " " + _message);
                    }
                }
                else
                {
                    Client *dest = server->get_client_by_nickname(*it);
                    if (!dest)
                        throw Err_401(*it);
                    dest->message_client(client->get_message_prefix() + " NOTICE " + (*it) + " " + _message);
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
