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

bool strmatch(std::string pattern, std::string string)
{
	size_t		patsize, strsize, j;
    const char *pat = pattern.c_str();
    const char *str = string.c_str();

	patsize = std::strlen(pat);
	strsize = std::strlen(str);

	j = 0;
	for (size_t i = 0; i < patsize; i++)
	{
		if (pat[i] == '*')
		{
			if (pat[i + 1] == '\0')
				return (1);
			else if (pat[i + 1] == '?')
			{
				if (str[j + 1] == '\0')
					return (false);
				else
				{
					// int flag = 0;
					while (j < strsize)
					{
						if (ft::strmatch(pat + i + 1, str + j))
							return (true);
						j++;
					}
					return (false);
				}
			}
			else if (!std::strchr(str + j, pat[i + 1]))
				return (false);
			else
				j = std::strchr(str + j, pat[i + 1]) - str;
		}
		else if (pat[i] == '?')
		{
			if (!str[j])
				return (false);
			else
				j++;
		}
		else
		{
			if (pat[i] != str[j])
				return (false);
			else
				j++;
		}
	}
	if (str[j])
		return (false);
	return (true);
}

} // ft