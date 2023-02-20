#ifndef KICK_CMD_HPP
# define KICK_CMD_HPP

#include "../Command.hpp"
#include "../../util_funcs.hpp"

class Kick_cmd : public Command
{
private:
    std::string channel_strs;
    std::string user_strs;
    std::string message;

public:
    Kick_cmd() : Command("KICK")
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   it = args.begin();

        if (args.size() < 2)
        {
            throw Err_461("KICK");
        }
        channel_strs = *it++;
        user_strs = *it++;
        if (args.size() == 3)
            message = *it;
        else
            message = "";
    }

    // op, joined, invited, voice에서 제거
    virtual void execute(Server* server, Client* client)
    {
        Channel*        ch;
        Client*         user;


        ch = server->get_channel(channel_strs);
        user = server->get_client_by_nickname(user_strs);
        if (ch == NULL)
        {
            throw Err_403(channel_strs);
        }
        if (!ch->op->exist(client))
        {
            throw Err_482(channel_strs);
        }
        if (!ch->joined->exist(user))
        {
            throw Err_442(channel_strs);  // need check
        }

        ch->op->del(user);
        ch->joined->del(user);
        ch->invited->del(user);
        ch->voice->del(user);
        user->delete_channel(ch);
        ch->message_channel(":" + client->get_message_prefix() + " KICK " + channel_strs + user_strs + " :" + message);
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif