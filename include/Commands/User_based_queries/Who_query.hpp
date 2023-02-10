#ifndef WHO_QUERY_HPP
# define WHO_QUERY_HPP

#include "../Command.hpp"

/*

1. Command: WHO
2. Parameters: [<name> [<o>]]
3. Replies
    1. ERR_NOSUCHSERVER
    - RPL_WHOREPLY(352)
        
        "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
        
    - RPL_ENDOFWHO(315)
        
        "<name> :End of WHO list"
        

클라이언트가 제공한 <name> 매개 변수와 '일치하는' 정보 목록을 반환하는 쿼리를 생성하기 위해 클라이언트에 사용됨

<name> 매개 변수가 없으면 표시되는 모든 사용자가 나열됨

- 보이지 않는 사용자( + i 모드) 및 요청 클라이언트와 공통 채널이 없는 사용자
- 가능한 모든 항목과 일치하는 와일드 카드를 사용하여 동일한 결과를 얻을 수 있음
- name에 0이 들어와도 동일함

WHO에 전달 된 <name> 은 <name> 채널을 찾을 수 없는 경우 사용자의 호스트, 서버, 실제 이름 및 별명과 일치하는 결과를 반환

o 매개 변수가 전달되면 결과 중에서 오퍼레이터인 결과만 반환

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
        std::cout << "\n";
    }

    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute WHO" << std::endl;

        // 와일드 카드 제거
        _who_name.erase(std::remove(_who_name.begin(), _who_name.end(), '*'), _who_name.end());
        _who_name.erase(std::remove(_who_name.begin(), _who_name.end(), '?'), _who_name.end());

        std::list<Client *> clients = server->get_clients();
        std::list<Client *>::iterator it_clients = clients.begin();

        // 이름 찾기
        std::string::size_type find_realname;
        for (; it_clients != clients.end(); ++it_clients)
        {
            find_realname = (*it_clients)->get_realname().find(_who_name);
            if (find_realname != std::string::npos)
            {
                // 서버에 출력(나중에 지워야 함)
                std::cout << "Find client" << std::endl;
                std::cout << (*it_clients)->get_realname() << std::endl;
                
                // 352 RPL_WHOREPLY, <channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>
                std::string message = "352 " + client->get_nickname() + " " + (*it_clients)->get_nickname() + " " + \
                                        (*it_clients)->get_username() + " " + (*it_clients)->get_hostname() + " " + \
                                        (*it_clients)->get_servername() + " " + (*it_clients)->get_nickname() + \
                                        " H* :0 " + (*it_clients)->get_realname();
                client->message_client(message.c_str());
                break;
            }
        }
        // 315 RPL_ENDOFWHO, <name> :End of WHO list
        if (find_realname != std::string::npos)
        {
            std::string message = "315 " + client->get_nickname() + " " + _who_name + " :End of WHO list";
            client->message_client(message.c_str());
        }

        init_cmd();
    }

    virtual void init_cmd()
    {
        _who_name = "";
        _o = "";
        std::cout << "Init command" << std::endl;
    }

};

#endif
