#include "../../include/Commands/Command.hpp"

Command::Command(std::string name)
{
    this->name = name;
}

Command::~Command()
{
}
/*

client 등록
- nick, user를 모두 입력하면 등록된다. 
- pass가 있는 경우 입력해야 한다.

- pass가 있으나 입력하지 않고 등록한다면 에러 메세지를 보내며 연결을 끊는다.
- pass를 언제 사용하지는 중요하지 않고 등록 전에만 사용하면 된다.
- 등록을 일정 시간 동안 하지 않는다면 연결을 끊는다.

*/
void Command::execute_command(Server* server, Client* client)
{
    if (!client->is_auth() && !(this->name == "NICK" || this->name == "USER" || this->name == "PASS"))
        throw Err_notregistered(this->name);
    this->execute(server, client);
}
