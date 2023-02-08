#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class Irc_exception: std::exception
{
public:
    std::string message;
    
    ~Irc_exception() throw() {return ;}
    const char* what() const throw() { return message.c_str(); }
};

// ERR_NOSUCHNICK
class Err_401: Irc_exception
{
public:
    Err_401(std::string nickname)  { message = nickname + " :No such nick/channel"; }
};

// ERR_NOSUCHSERVER
class Err_402: Irc_exception
{
public:
    Err_402(std::string servername) { message = servername + " :No such server"; }
};

// ERR_NOSUCHCHANNEL
class Err_403: Irc_exception
{
public:
    Err_403(std::string channelname) { message = channelname + " :No such channel"; }
};

// ERR_CANNOTSENDTOCHAN
class Err_404: Irc_exception
{
public:
    Err_404(std::string channelname) { message = channelname + " :Cannot send to channel"; }
};

// ERR_TOOMANYCHANNELS
class Err_405: Irc_exception
{
public:
    Err_405(std::string channelname) { message = channelname + " :You have joined too many channels"; }
};

// ERR_WASNOSUCHNICK
class Err_406: Irc_exception
{
public:
    Err_406(std::string nickname) { message = nickname + " :There was no sush nickname"; }
};

// ERR_TOOMANYTARGETS
class Err_407: Irc_exception
{
public:
    Err_407(std::string target) { message = target + " :Duplicate recipients. No message delivered"; }
};

// ERR_NOORIGIN
class Err_409: Irc_exception
{
public:
    Err_409() { message = ":No origin specified"; }
};

// ERR_NORECIPIENT
class Err_411: Irc_exception
{
public:
    Err_411(std::string command) { message = ":No recipient given (" + command + ")"; }
};

// ERR_NOTEXTTOSEND
class Err_412: Irc_exception
{
public:
    Err_412() { message = ":No text to send"; }
};

// ERR_NOTOPLEVEL
class Err_413: Irc_exception
{
public:
    Err_413(std::string mask) { message = mask + " :No toplevel domain specified"; }
};

// ERR_UNKNOWNCOMMAND
class Err_421: Irc_exception
{
public:
    Err_421(std::string cmd) { message = cmd + " :Unknown command"; }
};

// ERR_NONICKNAMEGIVEN
class Err_431: Irc_exception
{
public:
    Err_431() { message = ":No nickname given"; }
};

// ERR_ERRONEUSNICKNAME
class Err_432: Irc_exception
{
public:
    Err_432(std::string nick) { message = nick + " :Erroneus nickname"; }
};

// ERR_NICKNAMEINUSE
class Err_433: Irc_exception
{
public:
    Err_433(std::string nick) { message = nick + " :Nickname is already in use"; }
};

// ERR_NICKCOLLISION
class Err_436: Irc_exception
{
public:
    Err_436(std::string nick) { message = nick + " :Nickname collision KILL"; }
};

// ERR_NOTONCHANNEL
class Err_442: Irc_exception
{
public:
    Err_442(std::string channel) { message = channel + " :You're not on that channel"; }
};

// ERR_USERSDISABLED
class Err_446: Irc_exception
{
public:
    Err_446() { message = ":User has been disabled"; }
};

// ERR_NOTREGISTERED
class Err_451: Irc_exception
{
public:
    Err_451() { message = ":You have not registered"; }
};

// ERR_NEEDMOREPARAMS
class Err_461: Irc_exception
{
public:
    Err_461(std::string command) { message = command + " :Not enough parameters"; }
};

// ERR_ALREADYREGISTRED
class Err_462: Irc_exception
{
public:
    Err_462() { message = ":You may not reregister"; }
};

// ERR_PASSWDMISMATCH
class Err_464: Irc_exception
{
public:
    Err_464() { message = ":Password incorrect"; }
};

// ERR_KEYSET
class Err_467: Irc_exception
{
public:
    Err_467(std::string command) { message = command + " :Channel key already set"; }
};

// // ERR_CHANNELISFULL
class Err_471: Irc_exception
{
public:
    Err_471(std::string channel) { message = channel + " :Cannot join channel (+l)"; }
};

// ERR_UNKNOWNMODE
class Err_472: Irc_exception
{
public:
    Err_472(std::string c) { message = c + " :is unknown mode char to me"; }
};

// ERR_INVITEONLYCHAN
class Err_473: Irc_exception
{
public:
    Err_473(std::string channel) { message = channel + " :Cannot join channel (+i)"; }
};

// ERR_BANNEDFROMCHAN
class Err_474: Irc_exception
{
public:
    Err_474(std::string channel) { message = channel + " :Cannot join channel (+b)"; }
};

// ERR_BADCHANNELKEY
class Err_475: Irc_exception
{
public:
    Err_475(std::string channel) { message = channel + " :Cannot join channel (+k)"; }
};

// ERR_NOPRIVILEGES
class Err_481: Irc_exception
{
public:
    Err_481() { message = ":Permission Denied- You're not an IRC operator"; }
};

// ERR_CHANOPRIVSNEEDED
class Err_482: Irc_exception
{
public:
    Err_482(std::string channel) { message = channel + " :You're not channel operator"; }
};

// ERR_CANTKILLSERVER
class Err_483: Irc_exception
{
public:
    Err_483() { message = ":You cant kill a server!"; }
};

// ERR_NOOPERHOST
class Err_491: Irc_exception
{
public:
    Err_491() { message = ":No O-lines for your host"; }
};

// ERR_UMODEUNKNOWNFLAG
class Err_501: Irc_exception
{
public:
    Err_501() { message = ":Unknown Mode flag"; }
};

// ERR_USERSDONTMATCH
class Err_502: Irc_exception
{
public:
    Err_502() { message = ":Cant change mode for other users"; }
};


#endif