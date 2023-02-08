#include "../include/util_funcs.hpp"

namespace ft
{

std::list<std::string> split(std::string input, char delimiter)
{
    std::list<std::string> answer;
    std::stringstream ss(input);
    std::string temp;

    while (std::getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return (answer);
}

int stoi(std::string str)
{
    int result = 0;
    std::stringstream ssInt(str);
    ssInt >> result;

    if (!ssInt.fail())
        return (-1);
    return result;
}

std::string str_toupper(std::string str)
{
    std::string::iterator   iter = str.begin();
    std::string::iterator   end = str.end();

    for (; iter != end; iter++)
        *iter = toupper(*iter);
    return (str);
}

} // ft