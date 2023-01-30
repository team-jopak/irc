#ifndef NICK_CMD_HPP
# define NICK_CMD_HPP

#include "../Command.hpp"

/*

1. Command: NICK
2. Parameters: <nickname> [ <hopcount> ]
3. Replies
    1. ERR_NONICKNAMEGIVEN
    2. ERR_NICKNAMEINUSE
    3. ERR_ERRONEUSNICKNAME
    4. ERR_NICKCOLLISION

사용자에게 별명을 부여하거나 이전 별명을 변경

hopcount는 해당 유저가 홈 서버에서 얼마나 멀리 떨어져 있는지 표시하기 위해 서버에서만 사용

로컬 연결인 경우 홉은 0

클라이언트가 hopcount를 설정한 경우는 무시함

직접 연결된 클라이언트로부터 동일한 NICK을 수신한 경우에는 로컬 클라이언트에 ERR_NICKCOLLISION을 발행하고 NICK 명령을 삭제하고 킬을 생성하지 않을 수 있음

*/

class Nick_cmd : public Command
{
private:
    std::string _nickname;

public:
    Nick_cmd() : Command("NICK")
    {
        _nickname = "";
    }


    virtual void parse_args(str_list args)
    {
        // 닉네임만 받는다.
        if (args.size() == 1)
        {
            return ;
        }
        
        // 최소 닉 길이?

        // 닉네임에 허용되는 단어들
        str_list_iter it_args = args.begin();
        if (check_special_char(*it_args) == false)
        {
            return ;
        }

        _nickname = *it_args;
    }

    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute NICK" << std::endl;

        std::list<Client *> clients = server->get_clients();
        std::list<Client *>::iterator it_clients = clients.begin();
        for (; it_clients != clients.end(); ++it_clients)
        {
            if ((*it_clients)->get_nickname() == _nickname)
            {
                return ;
            }
        }
        server->message_all(":" + client->get_nickname() + " NICK " + _nickname);
        client->set_nickname(_nickname);

        init_cmd();
    }

    bool check_special_char(std::string s, size_t i = 0)
    {
        for (; i < s.length(); i++)
        {
            if (!(s[i] >= 48 && s[i] <= 57) &&
                !(s[i] >= 65 && s[i] <= 90) &&
                !(s[i] >= 97 && s[i] <= 122))
                return true;
        }
    	return false;
    }

    virtual void init_cmd()
    {
        std::string _nickname;
        std::cout << "Init command" << std::endl;
    }

};

#endif
