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
        channel_strs.clear();
        user_strs.clear();
        message.clear();
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   it = args.begin();

        if (args.size() < 2)
        {
            throw Err_needmoreparams("KICK");
        }
        channel_strs = *it++;
        user_strs = *it++;
        if (args.size() >= 3)
        {
            for (; it != args.end(); it++)
                message += (*it) + " ";
            message.pop_back();
        }
        else
            message.clear();
    }

    // op, joined, invited, voice에서 제거
    virtual void execute(Server* server, Client* client)
    {
        Channel*        ch;
        Client*         user;
        std::string     msg;

        ch = server->get_channel(channel_strs);
        user = server->get_client_by_nickname(user_strs);
        if (ch == NULL)
        {
            throw Err_nosuchchannel(channel_strs);
        }
        if (!ch->op->exist(client))
        {
            throw Err_chanoprivsneeded(channel_strs);
        }
        if (!user || !ch->joined->exist(user))
        {
            throw Err_notonchannel(channel_strs);  // need check
        }
        msg = "KICK " + channel_strs + " " + user_strs + " " + message;
        server->reply->send_channel_exec(ch, client, msg);
        ch->leave(client);
        user->delete_channel(ch);
        if (ch->joined->size() == 0)
            server->delete_channel(ch);
        init_cmd();
    }

    virtual void init_cmd()
    {
        channel_strs.clear();
        user_strs.clear();
        message.clear();
    }

};

#endif