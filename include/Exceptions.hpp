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
class Err_401: public Irc_exception
{
public:
    Err_401(std::string nickname, bool is_nick)  {
        number = "401";
        message = nickname + " :No such " + (is_nick ? "nick" : "channel");
    }
};

// ERR_NOSUCHSERVER
class Err_402: public Irc_exception
{
public:
    Err_402(std::string servername) {number = "402", message = servername + " :No such server"; }
};

// ERR_NOSUCHCHANNEL
class Err_403: public Irc_exception
{
public:
    Err_403(std::string channelname) {number = "403", message = channelname + " :No such channel"; }
};

// ERR_CANNOTSENDTOCHAN
class Err_404: public Irc_exception
{
public:
    Err_404(std::string channelname) {number = "404", message = channelname + " :Cannot send to channel"; }
};

// ERR_TOOMANYCHANNELS
class Err_405: public Irc_exception
{
public:
    Err_405(std::string channelname) {number = "405", message = channelname + " :You have joined too many channels"; }
};

// ERR_WASNOSUCHNICK
class Err_406: public Irc_exception
{
public:
    Err_406(std::string nickname) {number = "406", message = nickname + " :There was no sush nickname"; }
};

// ERR_TOOMANYTARGETS
class Err_407: public Irc_exception
{
public:
    Err_407(std::string target) {number = "407", message = target + " :Duplicate recipients. No message delivered"; }
};

// ERR_NOORIGIN
class Err_409: public Irc_exception
{
public:
    Err_409() {number = "409", message = ":No origin specified"; }
};

// ERR_NORECIPIENT
class Err_411: public Irc_exception
{
public:
    Err_411(std::string command) {number = "411", message = ":No recipient given (" + command + ")"; }
};

// ERR_NOTEXTTOSEND
class Err_412: public Irc_exception
{
public:
    Err_412() {number = "412", message = ":No text to send"; }
};

// ERR_NOTOPLEVEL
class Err_413: public Irc_exception
{
public:
    Err_413(std::string mask) {number = "413", message = mask + " :No toplevel domain specified"; }
};

// ERR_UNKNOWNCOMMAND
class Err_421: public Irc_exception
{
public:
    Err_421(std::string cmd) {number = "421", message = cmd + " :Unknown command"; }
};

// ERR_NONICKNAMEGIVEN
class Err_431: public Irc_exception
{
public:
    Err_431() {number = "431", message = ":No nickname given"; }
};

// ERR_ERRONEUSNICKNAME
class Err_432: public Irc_exception
{
public:
    Err_432(std::string nick) {number = "432", message = nick + " :Erroneus nickname"; }
};

// ERR_NICKNAMEINUSE
class Err_433: public Irc_exception
{
public:
    Err_433(std::string nick) {number = "433", message = nick + " :Nickname is already in use"; }
};

// ERR_NICKCOLLISION
class Err_436: public Irc_exception
{
public:
    Err_436(std::string nick) {number = "436", message = nick + " :Nickname collision KILL"; }
};

// ERR_NOTONCHANNEL
class Err_442: public Irc_exception
{
public:
    Err_442(std::string channel) {number = "442", message = channel + " :You're not on that channel"; }
};

// ERR_USERSDISABLED
class Err_446: public Irc_exception
{
public:
    Err_446() {number = "446", message = ":User has been disabled"; }
};

// ERR_NOTREGISTERED
class Err_451: public Irc_exception
{
public:
    Err_451(std::string cmd) {number = "451", message = cmd + " :You have not registered"; }
};

// ERR_NEEDMOREPARAMS
class Err_461: public Irc_exception
{
public:
    Err_461(std::string command) {number = "461", message = command + " :Not enough parameters"; }
};

// ERR_ALREADYREGISTRED
class Err_462: public Irc_exception
{
public:
    Err_462() {number = "462", message = ":You may not reregister"; }
};

// ERR_PASSWDMISMATCH
class Err_464: public Irc_exception
{
public:
    Err_464() {number = "464", message = ":Password incorrect"; }
};

// ERR_KEYSET
class Err_467: public Irc_exception
{
public:
    Err_467(std::string command) {number = "467", message = command + " :Channel key already set"; }
};

// // ERR_CHANNELISFULL
class Err_471: public Irc_exception
{
public:
    Err_471(std::string channel) {number = "471", message = channel + " :Cannot join channel (+l)"; }
};

// ERR_UNKNOWNMODE
class Err_472: public Irc_exception
{
public:
    Err_472(std::string c) {number = "472", message = c + " :is unknown mode char to me"; }
};

// ERR_INVITEONLYCHAN
class Err_473: public Irc_exception
{
public:
    Err_473(std::string channel) {number = "473", message = channel + " :Cannot join channel (+i)"; }
};

// ERR_BANNEDFROMCHAN
class Err_474: public Irc_exception
{
public:
    Err_474(std::string channel) {number = "474", message = channel + " :Cannot join channel (+b)"; }
};

// ERR_BADCHANNELKEY
class Err_475: public Irc_exception
{
public:
    Err_475(std::string channel) {number = "475", message = channel + " :Cannot join channel (+k)"; }
};

// ERR_INVALIDCHAN
class Err_476: public Irc_exception
{
public:
    Err_476(std::string channel) {number = "476", message = channel + " :Invalid channel name"; }
};

// ERR_NOPRIVILEGES
class Err_481: public Irc_exception
{
public:
    Err_481() {number = "481", message = ":Permission Denied- You're not an IRC operator"; }
};

// ERR_CHANOPRIVSNEEDED
class Err_482: public Irc_exception
{
public:
    Err_482(std::string channel) {number = "482", message = channel + " :You're not channel operator"; }
};

// ERR_CANTKILLSERVER
class Err_483: public Irc_exception
{
public:
    Err_483() {number = "483", message = ":You cant kill a server!"; }
};

// ERR_NOOPERHOST
class Err_491: public Irc_exception
{
public:
    Err_491() {number = "491", message = ":No O-lines for your host"; }
};

// ERR_UMODEUNKNOWNFLAG
class Err_501: public Irc_exception
{
public:
    Err_501() {number = "501", message = ":Unknown Mode flag"; }
};

// ERR_USERSDONTMATCH
class Err_502: public Irc_exception
{
public:
    Err_502() {number = "502", message = ":Cant change mode for other users"; }
};

class Err_696: public Irc_exception
{
public:
    Err_696(std::string channel, std::string opt)
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

    Err_696(std::string channel, std::string opt, std::string arg) 
    {
        number = "696";
        if (opt == "l")
            message = channel + " l " + arg + " :Invalid limit mode parameter. Syntax: <limit>"; 
        
    }
};

class Err_697: public Irc_exception
{
public:
    Err_697(std::string mask) {number = "697", message = mask + " b :Channel ban list already contains " + mask; }
};

class Err_698: public Irc_exception
{
public:
    Err_698(std::string channel, std::string mask) { message = channel + " " + mask + " b :Channel ban list does not contain " + mask; }
};




#endif
