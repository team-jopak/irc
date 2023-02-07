#ifndef TOPIC_CMD_HPP
# define TOPIC_CMD_HPP

#include "../Command.hpp"

/*

1. Command: TOPIC
2. Parameters: <channel> [<topic>]
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_NOTONCHANNEL
    3. ERR_CHANOPRIVSNEEDED
    4. RPL_NOTOPIC
    5. RPL_TOPIC

채널의 주제를 변경하거나 보는데 사용

주어진 <topic>이 없는 경우 <channel> 채널에 대한 주제가 리턴

<topic> 매개변수가 있는 경우 채널 모드에서 이 작업을 허용하면 해당 채널의 주제가 변경됨


- topic 변경
127.000.000.001.50886-127.000.000.001.06667: TOPIC #a :asdfawefawef

127.000.000.001.06667-127.000.000.001.50886: :cpak!root@127.0.0.1 TOPIC #a :asdfawefawef


- 권한없는 topic 변경
127.000.000.001.54664-127.000.000.001.06667: TOPIC #a :aaaaa

127.000.000.001.06667-127.000.000.001.54664: :irc.local 442 cpak_ #a :You're not on that channel!


- topic 확인
127.000.000.001.54664-127.000.000.001.06667: TOPIC #a

127.000.000.001.06667-127.000.000.001.54664: :irc.local 332 cpak_ #a :asdfawefawef
:irc.local 333 cpak_ #a cpak!root@127.0.0.1 :1675661369

- ':' 문자 뒤에 있는 문자열이 모두 토픽으로 정해진다.
- ':' 문자가 없어도 두번째 인자부터 모두 토픽으로 여긴다.

- 변경 응답 : 호스트 / 332 / 닉네임 / 서버이름 / 토픽
- 호스트 / 333 / 닉네임 / 서버이름 / 클라이언트 이름 / 시간

*/

class Topic_cmd : public Command
{
private:
    std::string ch_name;
    std::string topic;

public:
    Topic_cmd() : Command("TOPIC")
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter       iter = args.begin();
        list_str_iter       end = args.end();
        std::stringstream   ss;

        ch_name = *iter++;
        while (iter != end)
        {
            ss << *iter;
            if (++iter != end)
                ss << " ";
        }
        topic = ss.str();
        if (topic[0] == ':')
            topic = topic.substr(1);
    }

    virtual void execute(Server* server, Client* client)
    {
        std::string         prefix = server->get_host();
        std::string         nickname = client->get_nickname();
        Channel*            ch = server->get_channel(this->ch_name);
        std::string         msg;

        if (ch == NULL)
        {
            // ERR_NOSUCHCHANNEL
        }

        if (topic.size() == 0)
        {
            server->reply->topic_332(client, ch, this->topic);
            server->reply->clock_333(client, ch);
        }
        else
        {
            if (ch->check_flag('t'))
            {
                if (ch->op->exist(client))
                    ch->set_topic(this->topic);
                else
                {
                    // 442 cpak_ #a :You're not on that channel!
                    return ;
                }
            }
            else
                ch->set_topic(this->topic);

            msg = "TOPIC " + ch->get_name() + " :" + this->topic;
            server->reply->broadcast_exec(client, ch, msg);
        }
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif
