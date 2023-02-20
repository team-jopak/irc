#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <iostream>

class Irc_exception
{
public:
    std::string message;
    std::string number;
};

// ERR_NOSUCHNICK
class Err_nosuchnick: public Irc_exception
{
public:
    Err_nosuchnick(std::string nickname, bool is_nick)  {
        number = "401";
        message = nickname + " :No such " + (is_nick ? "nick" : "channel");
    }
};

// ERR_NOSUCHSERVER
class Err_nosuchserver: public Irc_exception
{
public:
    Err_nosuchserver(std::string servername) {number = "402", message = servername + " :No such server"; }
};

// ERR_NOSUCHCHANNEL
class Err_nosuchchannel: public Irc_exception
{
public:
    Err_nosuchchannel(std::string channelname) {number = "403", message = channelname + " :No such channel"; }
};

// ERR_CANNOTSENDTOCHAN
class Err_cannotsendtochan: public Irc_exception
{
public:
    Err_cannotsendtochan(std::string channelname) {number = "404", message = channelname + " :Cannot send to channel"; }
};

// ERR_TOOMANYCHANNELS
class Err_toomanychannels: public Irc_exception
{
public:
    Err_toomanychannels(std::string channelname) {number = "405", message = channelname + " :You have joined too many channels"; }
};

// ERR_WASNOSUCHNICK
class Err_wasnosuchnick: public Irc_exception
{
public:
    Err_wasnosuchnick(std::string nickname) {number = "406", message = nickname + " :There was no sush nickname"; }
};

// ERR_TOOMANYTARGETS
class Err_toomanytargets: public Irc_exception
{
public:
    Err_toomanytargets(std::string target) {number = "407", message = target + " :Duplicate recipients. No message delivered"; }
};

// ERR_NOORIGIN
class Err_noorigin: public Irc_exception
{
public:
    Err_noorigin() {number = "409", message = ":No origin specified"; }
};

// ERR_NORECIPIENT
class Err_norecipient: public Irc_exception
{
public:
    Err_norecipient(std::string command) {number = "411", message = ":No recipient given (" + command + ")"; }
};

// ERR_NOTEXTTOSEND
class Err_notexttosend: public Irc_exception
{
public:
    Err_notexttosend() {number = "412", message = ":No text to send"; }
};

// ERR_NOTOPLEVEL
class Err_notoplevel: public Irc_exception
{
public:
    Err_notoplevel(std::string mask) {number = "413", message = mask + " :No toplevel domain specified"; }
};

// ERR_UNKNOWNCOMMAND
class Err_unknowncommand: public Irc_exception
{
public:
    Err_unknowncommand(std::string cmd) {number = "421", message = cmd + " :Unknown command"; }
};

// ERR_NONICKNAMEGIVEN
class Err_nonicknamegiven: public Irc_exception
{
public:
    Err_nonicknamegiven() {number = "431", message = ":No nickname given"; }
};

// ERR_ERRONEUSNICKNAME
class Err_erroneusnickname: public Irc_exception
{
public:
    Err_erroneusnickname(std::string nick) {number = "432", message = nick + " :Erroneus nickname"; }
};

// ERR_NICKNAMEINUSE
class Err_nicknameinuse: public Irc_exception
{
public:
    Err_nicknameinuse(std::string nick) {number = "433", message = nick + " :Nickname is already in use"; }
};

// ERR_NICKCOLLISION
class Err_nickcollision: public Irc_exception
{
public:
    Err_nickcollision(std::string nick) {number = "436", message = nick + " :Nickname collision KILL"; }
};

// ERR_NOTONCHANNEL
class Err_notonchannel: public Irc_exception
{
public:
    Err_notonchannel(std::string channel) {number = "442", message = channel + " :You're not on that channel"; }
};

// ERR_USERSDISABLED
class Err_usersdisabled: public Irc_exception
{
public:
    Err_usersdisabled() {number = "446", message = ":User has been disabled"; }
};

// ERR_NOTREGISTERED
class Err_notregistered: public Irc_exception
{
public:
    Err_notregistered(std::string cmd) {number = "451", message = cmd + " :You have not registered"; }
};

// ERR_NEEDMOREPARAMS
class Err_needmoreparams: public Irc_exception
{
public:
    Err_needmoreparams(std::string command) {number = "461", message = command + " :Not enough parameters"; }
};

// ERR_ALREADYREGISTRED
class Err_alreadyregistred: public Irc_exception
{
public:
    Err_alreadyregistred() {number = "462", message = ":You may not reregister"; }
};

// ERR_PASSWDMISMATCH
class Err_passwdmismatch: public Irc_exception
{
public:
    Err_passwdmismatch() {number = "464", message = ":Password incorrect"; }
};

// ERR_KEYSET
class Err_keyset: public Irc_exception
{
public:
    Err_keyset(std::string command) {number = "467", message = command + " :Channel key already set"; }
};

// // ERR_CHANNELISFULL
class Err_channelisfull: public Irc_exception
{
public:
    Err_channelisfull(std::string channel) {number = "471", message = channel + " :Cannot join channel (+l)"; }
};

// ERR_UNKNOWNMODE
class Err_unknownmode: public Irc_exception
{
public:
    Err_unknownmode(std::string c) {number = "472", message = c + " :is unknown mode char to me"; }
};

// ERR_INVITEONLYCHAN
class Err_inviteonlychan: public Irc_exception
{
public:
    Err_inviteonlychan(std::string channel) {number = "473", message = channel + " :Cannot join channel (+i)"; }
};

// ERR_BANNEDFROMCHAN
class Err_bannedfromchan: public Irc_exception
{
public:
    Err_bannedfromchan(std::string channel) {number = "474", message = channel + " :Cannot join channel (+b)"; }
};

// ERR_BADCHANNELKEY
class Err_badchannelkey: public Irc_exception
{
public:
    Err_badchannelkey(std::string channel) {number = "475", message = channel + " :Cannot join channel (+k)"; }
};

// ERR_INVALIDCHAN
class Err_invalidchan: public Irc_exception
{
public:
    Err_invalidchan(std::string channel) {number = "476", message = channel + " :Invalid channel name"; }
};

// ERR_NOPRIVILEGES
class Err_noprivileges: public Irc_exception
{
public:
    Err_noprivileges() {number = "481", message = ":Permission Denied- You're not an IRC operator"; }
};

// ERR_CHANOPRIVSNEEDED
class Err_chanoprivsneeded: public Irc_exception
{
public:
    Err_chanoprivsneeded(std::string channel) {number = "482", message = channel + " :You're not channel operator"; }
};

// ERR_CANTKILLSERVER
class Err_cantkillserver: public Irc_exception
{
public:
    Err_cantkillserver() {number = "483", message = ":You cant kill a server!"; }
};

// ERR_NOOPERHOST
class Err_nooperhost: public Irc_exception
{
public:
    Err_nooperhost() {number = "491", message = ":No O-lines for your host"; }
};

// ERR_UMODEUNKNOWNFLAG
class Err_umodeunknownflag: public Irc_exception
{
public:
    Err_umodeunknownflag() {number = "501", message = ":Unknown Mode flag"; }
};

// ERR_USERSDONTMATCH
class Err_usersdontmatch: public Irc_exception
{
public:
    Err_usersdontmatch() {number = "502", message = ":Cant change mode for other users"; }
};

// ERR_INVALIDPARM
class Err_invalidparm: public Irc_exception
{
public:
    Err_invalidparm(std::string channel, std::string opt)
    {
        number = "696";
        if (opt == "l")
            message = channel + " l * :You must specify a parameter for the limit mode. Syntax: <limit>";
        else if (opt == "k")
            message = channel + " k * :You must specify a parameter for the key mode. Syntax: <key>"; 
        else if (opt == "v")
            message = channel + " v * :You must specify a parameter for the voice mode. Syntax: <nick>"; 
        else if (opt == "o")
            message = channel + " o * :You must specify a parameter for the op mode. Syntax: <nick>"; 
    }

    Err_invalidparm(std::string channel, std::string opt, std::string arg) 
    {
        number = "696";
        if (opt == "l")
            message = channel + " l " + arg + " :Invalid limit mode parameter. Syntax: <limit>"; 
        
    }
};

class Err_chanalreadycontains: public Irc_exception
{
public:
    Err_chanalreadycontains(std::string mask) {number = "697", message = mask + " b :Channel ban list already contains " + mask; }
};

class Err_chandoesntcontain: public Irc_exception
{
public:
    Err_chandoesntcontain(std::string channel, std::string mask) { message = channel + " " + mask + " b :Channel ban list does not contain " + mask; }
};


class Connection_error
{
public:
    std::string message;

    Connection_error() { message = "ERROR :Closing link: (root@127.0.0.1) [Access denied by configuration]"; }
};

class Capls_error
{
public:
    Capls_error() {}
};


#endif
