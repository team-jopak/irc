#ifndef NAMES_CMD_HPP
# define NAMES_CMD_HPP

#include "../Command.hpp"

/*

1. Command: NAMES
2. Parameters: [<channel>{,<channel>}]
3. Replies
    1. RPL_NAMREPLY
    2. RPL_ENDOFNAMES

사용자가 볼 수 있는 모든 채널에서 볼 수 있는 모든 별명을 나열

채널 이름은 비공개(+p), 비밀(+s)이 아니거나 실제로 존재하는 이름

<channel> 매개 변수는 유효한 경우 정보를 반환 할 채널을 지정

잘못된 채널 이름에 대한 오류 응답이 없음

<channel> 매개 변수가 제공되지 않으면 모든 채널 및 해당 점유자의 목록이 리턴됨

목록의 끝에는 어느 채널에도 표시되지 않은 사용자 목록이 채널 *에 있는 것으로 표시 됨

NAMES 메시지에 응답하기 위해 RPL_NAMREPLY 및 RPL_ENDOFNAMES로 구성된 응답 쌍이 서버에 의해 클라이언트로 다시 전송됩니다. 
쿼리에서와 같이 채널이 없으면 RPL_ENDOFNAMES만 반환됩니다. 
이것에 대한 예외는 매개 변수없이 NAMES 메시지가 전송되고 모든 보이는 채널과 내용이 끝을 표시하기 위해 
RPL_ENDOFNAMES가 있는 일련의 RPL_NAMEREPLY 메시지로 다시 전송되는 경우입니다.



- client가 해당 채널에 들어온 후에 names 명령어로 유저를 확인할 수 있다.

- private인 경우
names #a
:irc.local 353 aaa * #a :aaa @cpak__ cpak____2 cpak_____ cpak____ cpak___ cpak
:irc.local 366 aaa #a :End of /NAMES list.

- secret인 경우
names #a
:irc.local 353 aaa @ #a :aaa @cpak__ cpak____2 cpak_____ cpak____ cpak___ cpak
:irc.local 366 aaa #a :End of /NAMES list.

- 아닌 경우
names #a
:irc.local 353 aaa = #a :aaa @cpak__ cpak____2 cpak_____ cpak____ cpak___ cpak
:irc.local 366 aaa #a :End of /NAMES list.

- 채널이 존재하지 않는 경우
names #asdfawefon
:irc.local 366 aaa #asdfawefon :End of /NAMES list.

- 인자가 없는 경우
names
:irc.local 366 aaa * :End of /NAMES list.

/ hostname / n / nick / [*|@|=] / channel / : / [@|+]nick [...] /

nick 앞에 op라면 '@', voice라면 '+'가 붙는다. 만약에 두개의 권한을 가졌다면 '@'가 붙는다.
channel 앞에 private이라면 '*', secret이라면 '@', 아무것도 아니라면 '='가 붙는다.

*/

class Names_cmd : public Command
{
private:
    std::list<std::string>  ch_list;

public:
    Names_cmd() : Command("NAMES")
    {
    }

    // 콤마로 구분된 채널명을 파싱한다.
    // 첫번째 인자만 처리한다.
    virtual void parse_args(list_str args)
    {
        this->ch_list = ft::split_list(*(args.begin()), ',');
    }

    // 채널명으로 채널을 가져와서 client가 참여하고 있는지 확인
    // 참여하고 있지 않다면 endline
    // 참여하고 있다면 list을 출력
    // 채널에 참여하고 있는 client의 권한을 확인하여 nickname 앞에 @ 또는 +를 붙인다.
    // voice에만 포함되어 있으면 +, op에 있다면 무조건 @
    virtual void execute(Server* server, Client* client)
    {
        list_str_iter   iter = this->ch_list.begin();
        list_str_iter   end = this->ch_list.end();
        Channel*        ch;

        for (; iter != end; iter++)
        {
            ch = server->get_channel(*iter);
            if (ch != NULL && ch->joined->exist(client))
                server->reply->namreply_353(client, ch);
            server->reply->endofnames_366(client, ch);
        }
        init_cmd();
    }

    virtual void init_cmd()
    {
        ch_list.clear();
    }
};

#endif
