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

<<<<<<< HEAD
    // 그냥 벡터를 넘겨줘서 it랑 길이 등 다른 함수도 사용할 수 있는게 좋을 듯?
=======

>>>>>>> feature/20/create_Pass_cmd_class
    virtual void parse_args(str_list args)
    {
        // 벡터 길이가 주어진다면 에러처리(패스워드는 하나만 들어오면 된다)
        if (args.size() != 1)
        {
            return ;
        }

        str_list_iter it_args = args.begin();
        _password = *it_args;

        (void)args;
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        std::cout << "Execute NICK" << std::endl;
        std::cout << "\n";
    }

    // 해당 클라이언트 클래스도 넘어와야 할 듯
    virtual void execute(Server* server, Client* client)
    {
        std::cout << "\n";
    }

    // 해당 클라이언트 클래스도 넘어와야 할 듯
    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute PASS" << std::endl;

        // 해당 클라이언트가 권한이 있다면 return
        if (client->is_auth() == true)
        {
            return ;
        }

        // 서버클래스가 들어와 비밀번호를 확인해야 할 듯?
        if (_password == server->get_password())
        {
            // 해당 클라이언트에게 권한을 부여한다.
            client->get_auth();
        }

        init_cmd();
    }

    virtual void init_cmd()
    {
        _password = "";
        std::cout << "Init command" << std::endl;
    }

};

#endif
