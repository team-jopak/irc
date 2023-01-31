#ifndef FUNCTIONS_HPP
# define FUNCTIONS_HPP

#include <list>
#include <string>
#include <sstream>

std::list<std::string> ft_split(std::string input, char delimiter) 
{
    std::list<std::string> answer;
    std::stringstream ss(input);
    std::string temp;

    while (std::getline(ss, temp, delimiter)) 
    {
        answer.push_back(temp);
    }

    return (answer);
}

#endif