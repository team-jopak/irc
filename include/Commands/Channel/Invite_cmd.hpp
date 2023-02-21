#ifndef INVITE_CMD_HPP
# define INVITE_CMD_HPP

#include "../Command.hpp"

/*
      Command: INVITE
   Parameters: <nickname> <channel>

   The INVITE message is used to invite users to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  To invite a user to a channel which is invite only (MODE
   +i), the client sending the invite must be recognised as being a
   channel operator on the given channel.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
           RPL_INVITING                    RPL_AWAY

   Examples:

   :Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel
                                   #Dust

   INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
                                   #Twilight_zone

    127.000.000.001.37892-127.000.000.001.06667: INVITE cpak_ #qwer

    127.000.000.001.06667-127.000.000.001.37892: :irc.local 341 aaa cpak_ :#qwer

    127.000.000.001.06667-127.000.000.001.52970: :aaa!root@127.0.0.1 INVITE cpak_ :#qwer
*/

class Invite_cmd : public Command
{
private:
    std::string nickname;
    std::string channel;

public:
    Invite_cmd() : Command("INVITE")
    {
    }

    ~Invite_cmd()
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   iter = args.begin();

        if (args.size() < 2)
            throw Err_needmoreparams("INVITE");
        this->nickname = *iter++;
        this->channel = *iter;
    }

    virtual void execute(Server* server, Client* client)
    {
        Client*     tar = server->get_client_by_nickname(this->nickname);
        Channel*    ch = server->get_channel(this->channel);

        if (ch == NULL)
            throw Err_nosuchchannel(this->channel);
        if (tar == NULL)
            throw Err_nosuchnick(this->nickname, true);
        if (!ch->joined->exist(client))
            throw Err_notonchannel(this->channel);
        if (ch->joined->exist(tar))
            throw Err_useronchannel(this->nickname, this->channel);
        if (!ch->op->exist(client))
            throw Err_chanoprivsneeded(this->channel);
        server->reply->inviting_341(client, ch, this->nickname);
        server->reply->away_301(client, ch, tar);
        ch->invited->add(tar);
        init_cmd();
    }

    virtual void init_cmd()
    {
        nickname.clear();
        channel.clear();
    }
};

#endif