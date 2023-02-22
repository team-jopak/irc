#ifndef PASS_CMD_HPP
# define PASS_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PASS
2. Parameter: <password>
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_ALREADYREGISTRED

연결 암호 설정

연결 등록(NICK/USER/SERVER)를 시도하기 전에 암호를 설정할 수 있음

등록 이전에 여러 PASS를 보낼 수 있지만 마지막으로 보낸 명령만 확인에 사용되며 등록된 이후에는 변경할 수 없습니다

*/

class Pass_cmd : public Command
{
private:
    std::string _password;


public:
    Pass_cmd() : Command("PASS")
    {
        _password = "";
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter iter = args.begin();
        list_str_iter end = args.end();
    
        if (args.size() == 0)
            throw Err_needmoreparams("PASS");
        std::cout << args.size() << std::endl;
        for (; iter != end; iter++)
        {
            _password += *iter;
            _password += " ";
        }
        std::string::iterator it = _password.end() - 1;
        while ((*it) == ' ')
        {
            _password.erase(_password.rfind(' '));
            it = _password.end() - 1;
        }
    }

    virtual void execute(Server* server, Client* client)
    {
        if (client->is_auth() == true)
            throw Err_alreadyregistred();
        if (_password == server->get_password())
            client->set_auth(this->name);
        init_cmd();
    }

    virtual void init_cmd()
    {
        _password = "";
    }

};

#endif
