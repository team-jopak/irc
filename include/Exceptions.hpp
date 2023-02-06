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