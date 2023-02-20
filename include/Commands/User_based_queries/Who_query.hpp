#ifndef WHO_QUERY_HPP
# define WHO_QUERY_HPP

#include "../Command.hpp"

/*

1. Command: WHO
2. Parameters: [<name> [<o>]]
3. Replies
    1. ERR_NOSUCHSERVER // 사용 안함
    - RPL_WHOREPLY(352)
        
        "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"

        H: The user is available
        G: The user is away // 자리비움같은 옵션?
        *: The user is an IRC operator
        @: The user is a channel operator
        +: The user is a channel voice
        
    - RPL_ENDOFWHO(315)
        
        "<name> :End of WHO list"


클라이언트가 제공한 <name> 매개 변수와 '일치하는' 정보 목록을 반환하는 쿼리를 생성하기 위해 클라이언트에 사용됨

<name> 매개 변수가 없으면 표시되는 모든 사용자가 나열됨

- 보이지 않는 사용자( + i 모드) 및 요청 클라이언트와 공통 채널이 없는 사용자
- 가능한 모든 항목과 일치하는 와일드 카드를 사용하여 동일한 결과를 얻을 수 있음
- name에 0이 들어와도 동일함

WHO에 전달 된 <name> 은 <name> 채널을 찾을 수 없는 경우 사용자의 호스트, 서버, 실제 이름 및 별명과 일치하는 결과를 반환

o 매개 변수가 전달되면 결과 중에서 오퍼레이터인 결과만 반환

:irc.local 352 hyujo #lo3 root 127.0.0.1 irc.local hyujo H@ :0 root
:irc.local 315 hyujo hyujo :End of /WHO list.

*/

class Who_query : public Command
{
private:
    std::string _who_name;
    std::string _o;

public:
    Who_query() : Command("WHO")
    {
    }

    virtual void parse_args(list_str args)
    {
        // pass, nick, user, oper 까지 명령어 입력이 되야 한다.

        list_str_iter it_args = args.begin();

        if (args.size() > 2 || args.size() == 0)
        {
            throw Err_461("WHO");
        }

        _who_name = *it_args;
        if (args.size() == 2)
        {
            it_args++;
            _o = *it_args;
        }
    }

    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute WHO" << std::endl;

        // 채널 찾기
        if (_who_name[0] == '#')
        {
            Channel* channel = server->get_channel(_who_name);
            if (channel != NULL)
            {
                std::list<Client *>  clients = channel->get_clients();
                std::list<Client *>::iterator it_clients = clients.begin();
                for (; it_clients != clients.end(); ++it_clients)
                {
                    send_message(client, it_clients);
                }

            }
        }
        // 이름 찾기
        else
        {
            std::list<Client *> clients = server->get_clients();
            std::list<Client *>::iterator it_clients = clients.begin();
            for (; it_clients != clients.end(); ++it_clients)
            {
                // nick 이름인지
                if (ft::strmatch(_who_name, (*it_clients)->get_nickname()))
                {
                    // 서버에 출력(나중에 지워야 함)
                    std::cout << "Find client" << std::endl;
                    std::cout << (*it_clients)->get_nickname() << std::endl;
                    
                    // oper 가 있는 클라이언트 들만 전송
                    if (_o.compare("o") && (*it_clients)->is_oper())
                    {
                        send_message(client, it_clients);
                        break ;
                    }
                    // 모든 클라이언트에게 전송
                    else if (_o.compare("o") == -1)
                    {
                        send_message(client, it_clients);
                        break ;
                    }
                }
            }
        }
        // 315 RPL_ENDOFWHO, <name> :End of WHO list
        std::string message = "315 " + client->get_nickname() + " " + _who_name + " :End of WHO list";
        client->message_client(message.c_str());

        init_cmd();
    }

    virtual void init_cmd()
    {
        _who_name = "";
        _o = "";
        std::cout << "Init command" << std::endl;
    }

    void send_message(Client* client, std::list<Client *>::iterator it_clients)
    {
        // 채널
        // :penguin.omega.example.org 352 hyu_ #lo1 hyunjinjo 127.0.0.1 penguin.omega.example.org hyu_ H@ :0 HYUNJIN JO
        // 이름
        // :penguin.omega.example.org 352 hyu_ #lo1 hyunjinjo 127.0.0.1 penguin.omega.example.org hyu_ H@ :0 HYUNJIN JO

        // 채널인지 이름인지 확인
        Channel *channel = client->get_last_channel();
        std::string channelname = "*";
        if (channel != NULL)
        {
            channelname = channel->get_name();
        }

        // IRC operator 인지 확인
        std::string oper_option = "";
        if ((*it_clients)->is_oper() == true)
        {
            oper_option = "*";
        }

        // @, + 옵션 추가
        std::string co_v_option = "";
        // 해당 채널에서 오퍼레이터인지 확인
        if (channel && channel->op->exist(*it_clients) == true)
        {
            co_v_option = "@";
        }
        // 해당 채널에서 보이스인지 확인
        else if (channel && channel->voice->exist(*it_clients) == true)
        {
            co_v_option = "+";
        }

        // 352 RPL_WHOREPLY, <channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>
        std::string message = ":irc.local 352 " + client->get_nickname() + " " + channelname + " " + \
                                (*it_clients)->get_username() + " " + (*it_clients)->get_hostname() + " " + \
                                (*it_clients)->get_servername() + " " + (*it_clients)->get_nickname() + \
                                " H" + oper_option + co_v_option +  " :0 " + (*it_clients)->get_realname();

        // std::string message = ":irc.local 352 " + std::string("*") + " " + channel->get_name() + " " + \
        //                         (*it_clients)->get_username() + " " + (*it_clients)->get_hostname() + " " + \
        //                         (*it_clients)->get_servername() + " " + (*it_clients)->get_nickname() + \
        //                         " H @ : 0 " + (*it_clients)->get_realname();
        client->message_client(message.c_str());
    }

};

#endif
