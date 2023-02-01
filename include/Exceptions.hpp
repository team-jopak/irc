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

#endif