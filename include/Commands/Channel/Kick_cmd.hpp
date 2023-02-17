#ifndef KICK_CMD_HPP
# define KICK_CMD_HPP

#include "../Command.hpp"
#include "../../util_funcs.hpp"

class Kick_cmd : public Command
{
private:
<<<<<<< HEAD
    std::string channel_strs;
    std::string user_strs;
=======
    list_str    channel_strs;
    list_str    user_strs;
>>>>>>> 3933cda920f4ebae86d64c71c8e1713d389a5c1a
    std::string message;

public:
    Kick_cmd() : Command("KICK")
    {
    }

    virtual void parse_args(list_str args)
    {
        list_str_iter   it = args.begin();

        channel_strs = *it++;
        user_strs = *it++;
        message = *it;
    }

    // op, joined, invited, voice에서 제거
    virtual void execute(Server* server, Client* client)
    {
        Channel*        ch;
        Client*         user;

        user = server->get_client_by_nickname(user_strs);
        if (channel_strs.size() == 0 || user_strs.size() == 0)
        {
            // ERR_NEEDMOREPARAMS
        }

<<<<<<< HEAD
        ch = server->get_channel(channel_strs);
=======
        ch = server->get_channel(*iter);
>>>>>>> 3933cda920f4ebae86d64c71c8e1713d389a5c1a
        if (ch == NULL)
        {
            // ERR_NOSUCHCHANNEL
        }

        if (!ch->joined->exist(user))
        {
            // ERR_NOTONCHANNEL
        }

        ch->op->del(user);
        ch->joined->del(user);
        ch->invited->del(user);
        ch->voice->del(user);
        user->delete_channel(ch);
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif