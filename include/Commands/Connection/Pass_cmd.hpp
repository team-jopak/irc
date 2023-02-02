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

    // 클라이언트 넘겨서 어떤 클라이언트에 에러 메시지를 보내줘야 하는지 알아야 한다. 
    virtual void parse_args(str_list args)
    {
        str_list_iter it_args = args.begin();
    
        // 벡터 길이가 주어진다면 에러처리(패스워드는 하나만 들어오면 된다)
        if (args.size() != 1)
        {
            // 클라이언트로 메세지 보내야 한다.
            return serverResponse((*it_args), 4);
            // return ;
        }

        _password = *it_args;

        std::cout << "\n";
    }

    // 해당 클라이언트 클래스도 넘어와야 할 듯
    virtual void execute(Server* server, Client* client)
    {
        std::cout << "Execute PASS" << std::endl;

        // 해당 클라이언트가 권한이 있다면 return
        if (client->is_auth() == true)
        {
            // throw err_462() ;
            return ;
        }

        // 서버클래스가 들어와 비밀번호를 확인해야 할 듯?
        if (_password == server->get_password())
        {
            // 해당 클라이언트에게 권한을 부여한다.
            client->set_auth();
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
