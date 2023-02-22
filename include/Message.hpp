#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <list>

#include "Commands/Cmd_includes.hpp"
#include "util_funcs.hpp"

class Message 
{
public:
    typedef std::list<std::string>          list_str;
    typedef list_str::iterator              list_str_iter;
    typedef std::map<std::string, Command*> cmd_map;
    typedef cmd_map::iterator               cmd_map_iter;

    cmd_map		commands;
    
    Message();
    ~Message();

    Command*	parse_msg(std::string msg);

private:
    bool		_is_command(std::string str);
    bool		_is_prefix(std::string str);
    std::string	_remove_nl(std::string str);
    bool        _is_unknown_cmd(std::string cmd);
};

#endif
