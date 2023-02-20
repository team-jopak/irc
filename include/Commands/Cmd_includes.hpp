#ifndef CMD_INCLUDES_HPP
# define CMD_INCLUDES_HPP

// Channel
#include "Channel/Join_cmd.hpp"
#include "Channel/Kick_cmd.hpp"
#include "Channel/List_cmd.hpp"
#include "Channel/Mode_cmd.hpp"
#include "Channel/Names_cmd.hpp"
#include "Channel/Part_cmd.hpp"
#include "Channel/Topic_cmd.hpp"

// Connection
#include "Connection/Nick_cmd.hpp"
#include "Connection/Oper_cmd.hpp"
#include "Connection/Pass_cmd.hpp"
#include "Connection/Quit_cmd.hpp"
#include "Connection/Server_cmd.hpp"
#include "Connection/Squit_cmd.hpp"
#include "Connection/User_cmd.hpp"

// Miscellaneous_messages
#include "Miscellaneous_messages/Error_cmd.hpp"
#include "Miscellaneous_messages/Kill_cmd.hpp"
#include "Miscellaneous_messages/Ping_cmd.hpp"
#include "Miscellaneous_messages/Pong_cmd.hpp"

// Send_message
#include "Send_messages/Notice_cmd.hpp"
#include "Send_messages/Privmsg_cmd.hpp"

// User_based_queries
#include "User_based_queries/Who_query.hpp"
#include "User_based_queries/Whois_query.hpp"
#include "User_based_queries/Whowas_query.hpp"

#endif
