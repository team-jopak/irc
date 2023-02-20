#ifndef PART_CMD_HPP
# define PART_CMD_HPP

#include "../Command.hpp"

/*

1. Command: PART
2. Parameters: <channel>{,<channel>}
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_NOTONCHANNEL
    3. ERR_NOSUCHCHANNEL

메시지를 보내는 클라이언트가 매개 변수 문자열에 나열된 모든 주어진 채널의 활성 사용자 목록에서 제거되도록 함

127.000.000.001.59774-127.000.000.001.06667: PART #lo

127.000.000.001.06667-127.000.000.001.59774: :kelnf!root@127.0.0.1 PART :#lo

*/

class Part_cmd : public Command
{
private:
    list_str    channel_strs;

public:
    Part_cmd() : Command("PART")
    {
    }

    virtual void parse_args(list_str args)
    {
        channel_strs = ft::split_list(*(args.begin()), ',');
    }

    virtual void execute(Server* server, Client* client)
    {
        list_str_iter   iter = channel_strs.begin();
        list_str_iter   end = channel_strs.end();
        Channel*        ch;

        if (channel_strs.size() == 0)
            throw Err_needmoreparams("PART");
        for (; iter != end; iter++)
        {
            ch = server->get_channel(*iter);
            if (ch == NULL)
                throw Err_nosuchchannel(*iter);
            if (!ch->joined->exist(client))
                throw Err_notonchannel(ch->get_name());
            server->reply->send_channel_exec(ch, client, "PART :" + ch->get_name());
            ch->leave(client);
            client->delete_channel(ch);
            server->reply->send_channel_exec_except(ch, client, "PART :" + *iter);
        }
        init_cmd();
    }

    virtual void init_cmd()
    {
        channel_strs.clear();
    }
};

#endif
