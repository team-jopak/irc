#ifndef JOIN_CMD_HPP
# define JOIN_CMD_HPP

#include "../Command.hpp"
#include "../../util_funcs.hpp"

/*

1. Command: JOIN
2. Parameters: <channel>{,<channel>} [<key>{,<key>}]
3. Replies
    1. ERR_NEEDMOREPARAMS
    2. ERR_INVITEONLYCHAN
    3. ERR_CHANNELISFULL
    4. ERR_NOSUCHCHANNEL
    5. ERR_BANNEDFROMCHAN
    6. ERR_BADCHANNELKEY
    7. ERR_BADCHANMASK // no longer in use;
    8. ERR_TOOMANYCHANNELS
    9. RPL_TOPIC

클라이언트가 특정 채널 청취를 시작하는데 사용

클라이언트가 채널에 참여 할 수 있는지 여부는 클라이언트가 연결된 서버에서만 확인

다른 모든 서버는 사용자가 다른 서버에서 수신되면 자동으로 사용자를 채널에 추가

영향을 주는 조건은 다음과 같음

1. 채널이 초대 전용인 경우 사용자를 초대해야 함
2. 사용자의 별명/사용자 이름/호스트 이름은 활성화된 ban과 일치하지 않아야 함
3. 설정된 경우 올바른 키(암호)를 제공해야 함

사용자가 채널에 가입하면 채널에 영향을 주는 서버가 수신하는 모든 명령에 대한 알림을 받음(MODE, KICK, PART, QUIT, PRIVMSG, NOTICE 포함)

각 서버가 채널에 있는 사용자를 찾을 수 있는 위치를 알 수 있도록 모든 서버에 브로드 캐스트되어야 함

이를 통해 PRIVMSG/NOTICE 메시지를 채널에 최적으로 전달할 수 있음

JOIN이 성공하면 사용자에게 채널의 주제(RPL_TOPIC)와 채널에 있는 사용자 목록(RPL_NAMREPLY)이 전송되며 여기에는 User join이 포함

   Examples:

   JOIN #foobar                    ; join channel #foobar.

   JOIN &foo fubar                 ; join channel &foo using key "fubar".

   JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
                                   and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
                                   and channel #bar using key "foobar".

   JOIN #foo,#bar                  ; join channels #foo and #bar.

   :WiZ JOIN #Twilight_zone        ; JOIN message from WiZ


- 채널은 이름을 사용하여 참조할 수 있다.
    - 길이는 최대 200자이다.
    - ‘&’ 또는 ‘#’으로 시작된다.
    - 공백, ^G, 콤마를 포함할 수 없다.
    - ‘&’ 문자가 선행되면 존재하는 서버의 클라이언트만 가입할 수 있다.

- 채널에 참여시 클라이언트가 채널에 참여할 수 있는지 확인한다.
	- 사설, 비밀, 초대, 회의
	- 채널의 현재 모드에 따라 확인하는 것이 다르다.
    - 초대 채널방 : 초대장 확인
	- 비밀 채널방 : 올바른 키 입력 확인

    - ban 목록 확인 (만약에 초대되었다면 참석 가능하다)

- 없는 채널인 경우, 새로운 채널이 생성된다.
    - 채널장은 채널을 생성한 클라이언트


- RPL_TOPIC

    405 cpak #ff :You are on too many channels


    127.000.000.001.53776-127.000.000.001.06667: JOIN #a

    127.000.000.001.06667-127.000.000.001.53776: :cpak_!root@127.0.0.1 JOIN :#a
    :irc.local 332 cpak_ #b :aaaaa
    :irc.local 333 cpak_ #b cpak!root@127.0.0.1 :1675900578
    :irc.local 353 cpak_ = #a :cpak__ cpak cpak_
    :irc.local 366 cpak_ #a :End of /NAMES list.

    127.000.000.001.06667-127.000.000.001.43062: :cpak_!root@127.0.0.1 JOIN :#a

    127.000.000.001.06667-127.000.000.001.56940: :cpak_!root@127.0.0.1 JOIN :#a


    - 토픽이 설정된 경우
    127.000.000.001.53776-127.000.000.001.06667: JOIN #b

    127.000.000.001.06667-127.000.000.001.53776: :cpak_!root@127.0.0.1 JOIN :#b
    :irc.local 332 cpak_ #b :aaaaa
    :irc.local 333 cpak_ #b cpak!root@127.0.0.1 :1675900578
    :irc.local 353 cpak_ = #b :@cpak cpak_
    :irc.local 366 cpak_ #b :End of /NAMES list.

*/

class Join_cmd : public Command
{
private:
    list_str	names;
	list_str	pass;

public:
    Join_cmd() : Command("JOIN")
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   iter = args.begin();

        if (args.size() == 0)
			throw Err_461("JOIN");
		this->names = ft::split_list(*iter, ',');
        iter++;
        if (iter != args.end())
            this->pass = ft::split_list(*iter, ',');
    }

    virtual void execute(Server* server, Client* client)
    {
		list_str_iter 	name_iter = this->names.begin();
		list_str_iter 	name_end = this->names.end();
		list_str_iter 	pass_iter = this->pass.begin();
		list_str_iter 	pass_end = this->pass.end();
		Channel*		ch;

		for (; name_iter != name_end; name_iter++)
		{
			if (!check_name_validation(*name_iter))
				throw Err_476(*name_iter);
            if (!check_client_ch_limit(server, client))
                throw Err_405(*name_iter);
			ch = server->get_channel(*name_iter);
			if (ch != NULL)
            {
                if (ch->joined->exist(client))
                    continue ;
                ch->join(client, (pass_iter != pass_end) ? (*pass_iter++) : "");
            }
			else
				ch = server->add_channel(*name_iter, client);
            reply_join(client, ch, server);
		}
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

private:
	// 채널 이름 유효성 검사
	// - 최대 길이는 200자
    // - ‘&’ 또는 ‘#’으로 시작된다.
    // - 공백, ^G, 콤마를 포함할 수 없다.
	bool check_name_validation(std::string name)
	{
		return ((name.size() <= 200) && (name[0] == '#') && (name.find(7) == std::string::npos));
	}

    // 서버에 정해져있는 limit을 넘어가면 join을 사용할 수 없다.
    // limit은 client가 참여할 수 있는 채널수이다.
    bool check_client_ch_limit(Server* server, Client* client)
    {
        return(client->get_channel_size() < server->ch_limit);
    }

    // join 명령어를 실행하고 client에 응답 메시지를 보낸다.
    // 해당 channel에 topic이 있는 경우에만 topic 메시지를 추가한다.
    // 마지막에는 변경된 topic을 채널에 있는 client에게 모두 전달한다.
    void reply_join(Client* client, Channel* ch, Server* server)
    {
        server->reply->send_client_exec(client, "JOIN :" + ch->get_name());

        std::string s = ch->get_topic();
        if (s.size() != 0)
        {
            server->reply->topic_332(client, ch);
            server->reply->clock_333(client, ch);
        }
        server->reply->namreply_353(client, ch);
        server->reply->endofnames_366(client, ch);
        server->reply->send_channel_exec_except(ch, client, "JOIN :" + ch->get_name());
    }
};

#endif
