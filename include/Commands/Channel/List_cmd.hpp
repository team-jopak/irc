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

 - 서버 / 번호 / 이름 / 채널명 / 인원수 / [ 옵션 [key] [limit] ] / 주제

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

public:
    List_cmd() : Command("LIST")
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter iter = args.begin();
        list_str_iter end = args.end();

        for (; iter != end; iter++)
        {
            if ((*iter)[0] == '#')
                ch_name = *iter;
        }
    }

    virtual void execute(Server* server, Client* client)
    {
        server->reply->liststart_321(client);
        if (ch_name.size() != 0)
            server->reply->list_322(client, ch_name);
        else
        {
            list_ch       list = server->get_channel_list();
            list_ch_iter  iter = list.begin();
            list_ch_iter  end = list.end();

            for (; iter != end; iter++)
                server->reply->list_322(client, (*iter)->get_name());
        }
        server->reply->listend_323(client);
        init_cmd();
    }

    virtual void init_cmd()
    {
        ch_name = "";
    }
};

#endif
