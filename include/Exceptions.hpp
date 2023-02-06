#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

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

// class Wrong_command: public std::exception
// {
// private:
//     std::string _p;
// 
// public:
//     Wrong_command(std::string p)
//     {
//         _p = p;
//     }
//     const char* what() const throw() { return ("잘못된 명령어"); }
// };

// ERR_NOSUCHNICK
inline std::string err_401(std::string nickname) { return (nickname + " :No such nick/channel"); }
// ERR_NOSUCHSERVER
inline std::string err_402(std::string server_name) { return (server_name + " :No such server"); }
// ERR_NOSUCHCHANNEL
inline std::string err_403(std::string channel_name) { return (channel_name + " :No such channel"); }
// ERR_CANNOTSENDTOCHAN
inline std::string err_404(std::string channel_name) { return (channel_name + " :Cannot send to channel"); }
// ERR_TOOMANYCHANNELS
inline std::string err_405(std::string channel_name) { return (channel_name + " :You have joined too many channels"); }
// ERR_WASNOSUCHNICK
inline std::string err_406(std::string nickname) { return (nickname + " :There was no sush nickname"); }
// ERR_TOOMANYTARGETS
inline std::string err_407(std::string target) { return (target + " :Duplicate recipients. No message delivered"); }
// ERR_NOORIGIN
inline std::string err_409() { return (":No origin specified"); }
// ERR_NORECIPIENT
inline std::string err_411(std::string command) { return (":No recipient given (" + command + ")"); }
// ERR_NOTEXTTOSEND
inline std::string err_412() { return (":No text to send"); }
// ERR_NOTOPLEVEL
inline std::string err_413(std::string mask) { return (mask + " :No toplevel domain specified"); }
// ERR_NONICKNAMEGIVEN
inline std::string err_431() { return (":No nickname given"); }
// ERR_ERRONEUSNICKNAME
inline std::string err_432(std::string nick) { return (nick + " :Erroneus nickname"); }
// ERR_NICKNAMEINUSE
inline std::string err_433(std::string nick) { return (nick + " :Nickname is already in use"); }
// ERR_NICKCOLLISION
inline std::string err_436(std::string nick) { return (nick + " :Nickname collision KILL"); }
// ERR_NOTONCHANNEL
inline std::string err_442(std::string channel) { return (channel + " :You're not on that channel"); }
// ERR_USERSDISABLED
inline std::string err_446() { return (":User has been disabled"); }
// ERR_NOTREGISTERED
inline std::string err_451() { return (":You have not registered"); }
// ERR_NEEDMOREPARAMS
inline std::string err_461(std::string command) { return (command + " :Not enough parameters"); }
// ERR_ALREADYREGISTRED
inline std::string err_462() { return (":You may not reregister"); }
// ERR_PASSWDMISMATCH
inline std::string err_464() { return (":Password incorrect"); }
// ERR_KEYSET
inline std::string err_467(std::string command) { return (command + " :Channel key already set"); }
// // ERR_CHANNELISFULL
inline std::string err_471(std::string channel) { return (channel + " :Cannot join channel (+l)"); }
// ERR_UNKNOWNMODE
inline std::string err_472(std::string c) { return (c + " :is unknown mode char to me"); }
// ERR_INVITEONLYCHAN
inline std::string err_473(std::string channel) { return (channel + " :Cannot join channel (+i)"); }
// ERR_BANNEDFROMCHAN
inline std::string err_474(std::string channel) { return (channel + " :Cannot join channel (+b)"); }
// ERR_BADCHANNELKEY
inline std::string err_475(std::string channel) { return (channel + " :Cannot join channel (+k)"); }
// ERR_NOPRIVILEGES
inline std::string err_481() { return (":Permission Denied- You're not an IRC operator"); }
// ERR_CHANOPRIVSNEEDED
inline std::string err_482(std::string channel) { return (channel + " :You're not channel operator"); }
// ERR_CANTKILLSERVER
inline std::string err_483() { return (":You cant kill a server!"); }
// ERR_NOOPERHOST
inline std::string err_491() { return (":No O-lines for your host"); }
// ERR_UMODEUNKNOWNFLAG
inline std::string err_501() { return (":Unknown Mode flag"); }
// ERR_USERSDONTMATCH
inline std::string err_502() { return (":Cant change mode for other users"); }


#endif