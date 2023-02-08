#ifndef UTIL_FUNCS_HPP
# define UTIL_FUNCS_HPP

#include <list>
#include <string>
#include <sstream>

namespace ft
{

std::list<std::string>  split(std::string input, char delimiter); 
int                     stoi(std::string str);
std::string             str_toupper(std::string str);
bool                    strmatch(std::string pattern, std::string string);

}


#endif