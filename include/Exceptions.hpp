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

// ERR_NOSUCHNICK
class Err_401: public std::exception
{
private:
    std::string _message;

public:
    Err_401(std::string nickname) : _message(nickname + " :No such nick/channel") {}
    ~Err_401() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOSUCHSERVER
class Err_402: public std::exception
{
private:
    std::string _message;

public:
    Err_402(std::string servername) : _message(servername + " :No such server") {}
    ~Err_402() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOSUCHCHANNEL
class Err_403: public std::exception
{
private:
    std::string _message;

public:
    Err_403(std::string channelname) : _message(channelname + " :No such channel") {}
    ~Err_403() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_CANNOTSENDTOCHAN
class Err_404: public std::exception
{
private:
    std::string _message;

public:
    Err_404(std::string channelname) : _message(channelname + " :Cannot send to channel") {}
    ~Err_404() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_TOOMANYCHANNELS
class Err_405: public std::exception
{
private:
    std::string _message;

public:
    Err_405(std::string channelname) : _message(channelname + " :You have joined too many channels") {}
    ~Err_405() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_WASNOSUCHNICK
class Err_406: public std::exception
{
private:
    std::string _message;

public:
    Err_406(std::string nickname) : _message(nickname + " :There was no sush nickname") {}
    ~Err_406() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_TOOMANYTARGETS
class Err_407: public std::exception
{
private:
    std::string _message;

public:
    Err_407(std::string target) : _message(target + " :Duplicate recipients. No message delivered") {}
    ~Err_407() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOORIGIN
class Err_409: public std::exception
{
private:
    std::string _message;

public:
    Err_409() : _message(":No origin specified") {}
    ~Err_409() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NORECIPIENT
class Err_411: public std::exception
{
private:
    std::string _message;

public:
    Err_411(std::string command) : _message(":No recipient given (" + command + ")") {}
    ~Err_411() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOTEXTTOSEND
class Err_412: public std::exception
{
private:
    std::string _message;

public:
    Err_412() : _message(":No text to send") {}
    ~Err_412() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOTOPLEVEL
class Err_413: public std::exception
{
private:
    std::string _message;

public:
    Err_413(std::string mask) : _message(mask + " :No toplevel domain specified") {}
    ~Err_413() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NONICKNAMEGIVEN
class Err_431: public std::exception
{
private:
    std::string _message;

public:
    Err_431() : _message(":No nickname given") {}
    ~Err_431() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_ERRONEUSNICKNAME
class Err_432: public std::exception
{
private:
    std::string _message;

public:
    Err_432(std::string nick) : _message(nick + " :Erroneus nickname") {}
    ~Err_432() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NICKNAMEINUSE
class Err_433: public std::exception
{
private:
    std::string _message;

public:
    Err_433(std::string nick) : _message(nick + " :Nickname is already in use") {}
    ~Err_433() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NICKCOLLISION
class Err_436: public std::exception
{
private:
    std::string _message;

public:
    Err_436(std::string nick) : _message(nick + " :Nickname collision KILL") {}
    ~Err_436() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOTONCHANNEL
class Err_442: public std::exception
{
private:
    std::string _message;

public:
    Err_442(std::string channel) : _message(channel + " :You're not on that channel") {}
    ~Err_442() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_USERSDISABLED
class Err_446: public std::exception
{
private:
    std::string _message;

public:
    Err_446() : _message(":User has been disabled") {}
    ~Err_446() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOTREGISTERED
class Err_451: public std::exception
{
private:
    std::string _message;

public:
    Err_451() : _message(":You have not registered") {}
    ~Err_451() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NEEDMOREPARAMS
class Err_461: public std::exception
{
private:
    std::string _message;

public:
    Err_461(std::string command) : _message(command + " :Not enough parameters") {}
    ~Err_461() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_ALREADYREGISTRED
class Err_462: public std::exception
{
private:
    std::string _message;

public:
    Err_462() : _message(":You may not reregister") {}
    ~Err_462() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_PASSWDMISMATCH
class Err_464: public std::exception
{
private:
    std::string _message;

public:
    Err_464() : _message(":Password incorrect") {}
    ~Err_464() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_KEYSET
class Err_467: public std::exception
{
private:
    std::string _message;

public:
    Err_467(std::string command) : _message(command + " :Channel key already set") {}
    ~Err_467() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// // ERR_CHANNELISFULL
class Err_471: public std::exception
{
private:
    std::string _message;

public:
    Err_471(std::string channel) : _message(channel + " :Cannot join channel (+l)") {}
    ~Err_471() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_UNKNOWNMODE
class Err_472: public std::exception
{
private:
    std::string _message;

public:
    Err_472(std::string c) : _message(c + " :is unknown mode char to me") {}
    ~Err_472() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_INVITEONLYCHAN
class Err_473: public std::exception
{
private:
    std::string _message;

public:
    Err_473(std::string channel) : _message(channel + " :Cannot join channel (+i)") {}
    ~Err_473() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_BANNEDFROMCHAN
class Err_474: public std::exception
{
private:
    std::string _message;

public:
    Err_474(std::string channel) : _message(channel + " :Cannot join channel (+b)") {}
    ~Err_474() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_BADCHANNELKEY
class Err_475: public std::exception
{
private:
    std::string _message;

public:
    Err_475(std::string channel) : _message(channel + " :Cannot join channel (+k)") {}
    ~Err_475() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOPRIVILEGES
class Err_481: public std::exception
{
private:
    std::string _message;

public:
    Err_481() : _message(":Permission Denied- You're not an IRC operator") {}
    ~Err_481() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_CHANOPRIVSNEEDED
class Err_482: public std::exception
{
private:
    std::string _message;

public:
    Err_482(std::string channel) : _message(channel + " :You're not channel operator") {}
    ~Err_482() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_CANTKILLSERVER
class Err_483: public std::exception
{
private:
    std::string _message;

public:
    Err_483() : _message(":You cant kill a server!") {}
    ~Err_483() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_NOOPERHOST
class Err_491: public std::exception
{
private:
    std::string _message;

public:
    Err_491() : _message(":No O-lines for your host") {}
    ~Err_491() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_UMODEUNKNOWNFLAG
class Err_501: public std::exception
{
private:
    std::string _message;

public:
    Err_501() : _message(":Unknown Mode flag") {}
    ~Err_501() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};

// ERR_USERSDONTMATCH
class Err_502: public std::exception
{
private:
    std::string _message;

public:
    Err_502() : _message(":Cant change mode for other users") {}
    ~Err_502() throw() {return ;}
    
    const char* what() const throw() { return _message.c_str(); }
};


#endif