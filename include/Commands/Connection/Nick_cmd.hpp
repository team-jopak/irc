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
    4. ERR_NICKCOLLISION // 어디 사용 해야 할지?

사용자에게 별명을 부여하거나 이전 별명을 변경

hopcount는 해당 유저가 홈 서버에서 얼마나 멀리 떨어져 있는지 표시하기 위해 서버에서만 사용

로컬 연결인 경우 홉은 0

클라이언트가 hopcount를 설정한 경우는 무시함

직접 연결된 클라이언트로부터 동일한 NICK을 수신한 경우에는 로컬 클라이언트에 ERR_NICKCOLLISION을 발행하고 NICK 명령을 삭제하고 킬을 생성하지 않을 수 있음

닉네임 규칙은 다음과 같다
영어, (허용되는) 특수문자로 시작해야 한다
최대 9글자의 영어, 특수문자, 숫자 사용 가능하다
특수문자라 함은, [, ], \, ```, _, ^, {, |, } 만 가능하다

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

    virtual void parse_args(list_str args)
    {
        list_str_iter it_args = args.begin();

        if (args.size() != 1)
            throw Err_needmoreparams("NICK");
        if ((*it_args).size() > 9)
            throw Err_erroneusnickname(*it_args);
        if (check_char(*it_args) == false)
            throw Err_erroneusnickname(*it_args);
        _nickname = *it_args;
    }

    // 서버에 클라이언트를 받아오는 함수 있어서 매개변수로 넘기지 않아도 될 거 같은데?
    virtual void execute(Server* server, Client* client)
    {
        if (server->get_client_by_nickname(_nickname) != NULL)
            throw Err_nicknameinuse(_nickname);
        client->set_nickname(_nickname);
        if (!client->is_auth())
            client->set_auth(this->name);
        else
            server->message_all(":" + client->get_message_prefix() + " NICK :" + _nickname);
        init_cmd();
    }

    bool check_char(std::string s, size_t i = 0)
    {
        // 첫번째 단어는 영어 또는 특수 문자만 가능
        if (!(s[0] >= 91 && s[0] <= 96) &&
            !(s[0] >= 65 && s[0] <= 90) &&
            !(s[0] >= 97 && s[0] <= 122) &&
            !(s[0] >= 123 && s[0] <= 125))
        {
            return false;
        }

        for (; i < s.length(); i++)
        {
            // 0-9, A-Z, [ \ ] ^ _ ', a-z, { | }
            if (!(s[i] >= 48 && s[i] <= 57) &&
                !(s[i] >= 65 && s[i] <= 90) &&
                !(s[i] >= 91 && s[i] <= 96) &&
                !(s[i] >= 97 && s[i] <= 122) &&
                !(s[i] >= 123 && s[i] <= 125))
            {
                return false;
            }
        }
    	return true;
    }

    virtual void init_cmd()
    {
        _nickname = "";
    }

};

#endif
