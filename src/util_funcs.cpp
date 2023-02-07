#include "../include/util_funcs.hpp"

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