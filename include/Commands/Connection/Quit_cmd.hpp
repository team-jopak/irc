#ifndef QUIT_CMD_HPP
# define QUIT_CMD_HPP

#include "../Command.hpp"

/*

1. Command: QUIT
2. Parameters: [ <Quit message> ]
3. Replies
    1. none

클라이언트 세선은 종료 메시지와 함께 종료

서버는 QUIT 메시지를 보내는 클라이언트에 대한 연결을 닫아야 함

"Quit message"가 제공되면 기본 메시지인 별명 대신 이 메시지가 전송

두 서버의 연결 끊김이 발생되면 종료 메시지는 두 서버의 이름으로 구성되며 공백으로 구분 됨

첫 번째 이름은 아직 연결되어 있는 서버의 이름이며 두 번째 이름은 연결이 끊어진 서버의 이름

클라이언트가 QUIT 명령을 내리지 않고 클라이언트 연결이 닫히면
(EX, 클라이언트가 죽고 소켓에서 EOF가 발생하는 경우) 서버는 이벤트의 특성을 반영하는 일종의 메시지로 종료 메시지를 채워야 함

*/

class Quit_cmd : public Command
{
private:
    std::string _message;

public:
    Quit_cmd() : Command("QUIT")
    {
        _message = "";
    }

<<<<<<< HEAD
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    virtual void parse_args(str_vec_iter begin, str_vec_iter end)
    {
        std::cout << "args : ";

        for (; begin != end; begin++)
        {
            std::cout << *begin << " ";
=======
=======
>>>>>>> Stashed changes
    virtual void parse_args(str_list args)
    {        
        str_list_iter it_args = args.begin();
        str_list_iter it_args_end = args.end();
        for (; it_args != it_args_end; it_args++)
        {
            std::cout << *it_args << " ";
            _message += *it_args + " ";
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
        }
        std::cout << "\n";
=======
    virtual void parse_args(str_list args)
    {
        std::cout << "args : ";

        (void)args;
>>>>>>> feature/20/create_Pass_cmd_class
    }

    virtual void execute(Server* server, Client* client)
    {
        (void)server;
        (void)client;
        std::cout << "Execute QUIT" << std::endl;

        server->message_all(":" + client->get_nickname() + " QUIT :" + _message);
        server->delete_client(client->get_socket_fd());

        init_cmd();
    }

    virtual void init_cmd()
    {
        _message = "";
        std::cout << "Init command" << std::endl;
    }

};

#endif
