#ifndef USER_CMD_HPP
# define USER_CMD_HPP

#include "../Command.hpp"
#include <algorithm>

/*

1. Command: USER
2. Parameters: <username> <hostname> <servername> <realname>
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_ALREADYREGISTRED

새로운 사용자의 사용자 이름, 호스트 이름, 서버 이름 및 실제 이름을 지정함

클라이언트로부터 user와 nick이 모두 수신 된 후에만 사용자가 등록되므로 IRC에 도착한 새 사용자를 나타내기 위해 서버 간 통신에 사용됨

접두사로는 해당 클라이언트의 NICK이 사용 됨

호스트 이름과 서버 이름은 클라이언트에서 오는 경우 서버에서 무시하지만 서버 간 통신에 사용됨

즉, USER가 전송되기 전에 NICK은 항상 원격 서버로 전송되어야 함

*/

class User_cmd : public Command
{
private:
    std::string _username;
    std::string _hostname;
    std::string _servername;
    std::string _realname;

public:
    User_cmd() : Command("USER")
    {
        _username = "";
        _hostname = "";
        _servername = "";
        _realname = "";
    }

    virtual void parse_args(list_str args)
    {
        if (args.size() <= 3)
            throw Err_461("USER");
        list_str_iter it_args = args.begin();
        _username = *(it_args);
        _hostname = *(++it_args);
        _servername = *(++it_args);
        ++it_args;
        for (;it_args != args.end();++it_args)
        {
            std::string::iterator it = find((*it_args).begin(), (*it_args).end(), ':');
            if (it != (*it_args).end())
            {
                (*it_args).erase(it);
                _realname += *it_args;
            }
            else
            {
                _realname += ' ';
                _realname += *(it_args);
            }
        }
    }

    virtual void execute(Server*, Client* client)
    {
        if ((client->is_auth()))
            throw Err_462();
        client->set_username(_username);
        client->set_hostname(_hostname);
        client->set_servername(_servername);
        client->set_realname(_realname);
        client->set_auth(this->name);
        init_cmd();
    }

    virtual void init_cmd()
    {
        _username = "";
        _hostname = "";
        _servername = "";
        _realname = "";
    }
};

#endif