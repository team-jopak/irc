#ifndef LIST_CMD_HPP
# define LIST_CMD_HPP

#include "../Command.hpp"

/*

1. Command: LIST
2. Parameters: [<channel>{,<channel>} [<server>]]
3. Replies
    1. ERR_NOSUCHSERVER
    2. RPL_LIST
    3. RPL_LISTSTART
    4. RPL_LISTEND

채널과 주제를 나열하는 데 사용됨

<channel> 매개 변수를 사용하면 해당 채널의 상태만 표시됨

쿼리를 생성하는 클라이언트가 실제로 해당 채널에 있지 않는 한 개인 채널은 주제 없이 채널 "Prv"로 나열

클라이언트가 해당 채널의 구성원이 아니면 비밀 채널이 전혀 나열되지 않음

:irc.local 321 cpak_ Channel :Users Name
:irc.local 322 cpak_ #b 1 :[+nt]
:irc.local 322 cpak_ #&b 1 :[+nt]
:irc.local 322 cpak_ #aaa 3 :[+nt]
:irc.local 322 cpak_ #weer 2 :[+mns] asdf
:irc.local 322 cpak_ * 1 :
:irc.local 322 cpak_ #a 5 :[+nt]
:irc.local 323 cpak_ :End of channel list.

 - 서버 / 번호 / 이름 / 채널명 / 인원수 / [ 옵션 [키] ] / 주제

 - 개인 채널인 경우 채널명을 * 으로 표시하고, 옵션은 표시하지 않는다.
 - 없는 채널명인 경우 빈 목록을 보낸다.

 - 채널명이 없는 경우 : 모든 채널을 출력
 - 채널명이 하나인 경우 : 한 채널을 출력
 - 여러 채널명인 경우 : 출력하지 않음

*/

class List_cmd : public Command
{
private:
    std::string ch_name;
    Server*     cmd_server;
    Client*     cmd_client;

public:
    List_cmd() : Command("LIST")
    {
    }

    virtual void parse_args(str_list args)
    {
        str_list_iter iter = args.begin();
        str_list_iter end = args.end();

        for (; iter != end; iter++)
        {
            if ((*iter)[0] == '#')
                ch_name = *iter;
        }
    }

    virtual void execute(Server* server, Client* client)
    {
        cmd_server = server;
        cmd_client = client;

        rpl_liststart_321();
        if (ch_name.size() != 0)
            rpl_list_322(*(server->get_channel(ch_name)));
        else
        {
            std::list<Channel *> list = server->get_channel_list();
            for_each(list.begin(), list.end(), rpl_list_322);
        }
        rpl_listend_323();

        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

private:
    // 리스트 시작 출력
    // :irc.local 321 cpak_ Channel :Users Name
    void rpl_liststart_321()
    {
    }

    // 리스트 마지막 출력
    // :irc.local 323 cpak_ :End of channel list.
    void rpl_listend_323()
    {
    }

    // 채널의 옵션을 확인하고 메시지를 보낸다.
    // s : 채널명을 * 으로 변경, 옵션을 : 으로 변경
    // p : 아무것도 출력하지 않는다.
    // :irc.local 322 cpak_ #weer 2 :[+mns] asdf
    void rpl_list_322(Channel &ch)
    {
        std::stringstream ss;
        std::string prefix = this->cmd_server->get_host();
        std::string nickname = this->cmd_client->get_nickname();
        std::string ch_name = ch.get_name();
        std::string ch_nums = std::to_string(ch.clients->clients.size());
        std::string ch_opt = ch.get_flag_str(cmd_client);
        std::string ch_topic = ch.get_topic();
        bool        is_joined = ch.clients->exist(cmd_client);

        if (!is_joined && ch.check_flag('s'))
            return ;
        else if (!is_joined && ch.check_flag('p'))
        {
            ch_name = "*";
            ch_opt = "";
            ch_topic = "";
        }

        ss << ":" << prefix << " 322 " << nickname << " ";
        ss << ch_name << " " << ch_nums << " :" << ch_opt << " " << ch_topic;
        std::cout << ss.str() << std::endl;
    }

};

#endif
