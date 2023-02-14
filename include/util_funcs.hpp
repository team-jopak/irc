#ifndef UTIL_FUNCS_HPP
# define UTIL_FUNCS_HPP

#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>


namespace ft
{

std::list<std::string>  split(std::string input, char delimiter); 
long                    stol(std::string str);
std::string				ltos(long val);
std::string             str_toupper(std::string str);
bool                    strmatch(std::string pattern, std::string string);
std::string				vec_str_join(std::vector<std::string> vec, std::string delim);

}


#endif
