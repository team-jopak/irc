#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <exception>

class Bad_auth: public std::exception
{
public:
    const char* what() const throw() { return ("잘못된 권한"); }
};

class Bad_args: public std::exception
{
public:
    const char* what() const throw() { return ("잘못된 매개변수"); }
};

class Wrong_command: public std::exception
{
public:
    const char* what() const throw() { return ("잘못된 명령어"); }
};

// ERR_NOSUCHNICK
std::string err_401(std::string nickname) { return (nickname + " :No such nick/channel"); }
// ERR_NOSUCHSERVER
// std::string err_402(std::string server_name) { return (server_name + " :No such server"); }
// // ERR_NOSUCHCHANNEL
// std::string err_403(std::string channel_name) { return (channel_name + " :No such channel"); }
// // ERR_CANNOTSENDTOCHAN
// std::string err_404(std::string channel_name) { return (channel_name + " :Cannot send to channel"); }
// // ERR_TOOMANYCHANNELS
// std::string err_405(std::string channel_name) { return (channel_name + " :You have joined too many channels"); }
// // ERR_WASNOSUCHNICK
// std::string err_406(std::string nickname) { return (nickname + " :There was no sush nickname"); }
// // ERR_TOOMANYTARGETS
// std::string err_407(std::string target) { return (target + " :Duplicate recipients. No message delivered"); }
// // ERR_NOORIGIN
// std::string err_409() { return (":No origin specified"); }
// // ERR_NORECIPIENT
// std::string err_411(std::string command) { return (":No recipient given (" + command + ")"); }
// // ERR_NOTEXTTOSEND
// std::string err_412() { return (":No text to send"); }
// // ERR_NOTOPLEVEL
// std::string err_413(std::string mask) { return (mask + " :No toplevel domain specified"); }
// // ERR_NONICKNAMEGIVEN
// std::string err_431() { return (":No nickname given"); }
// // ERR_ERRONEUSNICKNAME
// std::string err_432(std::string nick) { return (nick + " :Erroneus nickname"); }
// // ERR_NICKNAMEINUSE
// std::string err_433(std::string nick) { return (nick + " :Nickname is already in use"); }
// // ERR_NICKCOLLISION
// std::string err_436(std::string nick) { return (nick + " :Nickname collision KILL"); }
// // ERR_NOTONCHANNEL
// std::string err_442(std::string channel) { return (channel + " :You're not on that channel"); }
// // ERR_USERSDISABLED
// std::string err_446() { return (":User has been disabled"); }
// // ERR_NOTREGISTERED
// std::string err_451() { return (":You have not registered"); }
// // ERR_NEEDMOREPARAMS
// std::string err_461(std::string command) { return (command + " :Not enough parameters"); }
// // ERR_PASSWDMISMATCH
// std::string err_464() { return (":Password incorrect"); }
// // ERR_KEYSET
// std::string err_467(std::string command) { return (command + " :Channel key already set"); }
// // // ERR_CHANNELISFULL
// std::string err_471(std::string channel) { return (channel + " :Cannot join channel (+l)"); }
// // ERR_UNKNOWNMODE
// std::string err_472(std::string c) { return (c + " :is unknown mode char to me"); }
// // ERR_INVITEONLYCHAN
// std::string err_473(std::string channel) { return (channel + " :Cannot join channel (+i)"); }
// // ERR_BANNEDFROMCHAN
// std::string err_474(std::string channel) { return (channel + " :Cannot join channel (+b)"); }
// // ERR_BADCHANNELKEY
// std::string err_475(std::string channel) { return (channel + " :Cannot join channel (+k)"); }
// // ERR_NOPRIVILEGES
// std::string err_481() { return (":Permission Denied- You're not an IRC operator"); }
// // ERR_CHANOPRIVSNEEDED
// std::string err_482(std::string channel) { return (channel + " :You're not channel operator"); }
// // ERR_CANTKILLSERVER
// std::string err_483() { return (":You cant kill a server!"); }
// // ERR_NOOPERHOST
// std::string err_491() { return (":No O-lines for your host"); }
// // ERR_UMODEUNKNOWNFLAG
// std::string err_501() { return (":Unknown Mode flag"); }
// // ERR_USERSDONTMATCH
// std::string err_502() { return (":Cant change mode for other users"); }

#endif