#include "../include/util_funcs.hpp"

namespace ft
{

std::list<std::string> split_list(std::string input, char delimiter)
{
    std::list<std::string> answer;
    std::stringstream ss(input);
    std::string temp;

    while (std::getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return (answer);
}

std::vector<std::string> split_vec(std::string input, char delimiter)
{
    std::vector<std::string> answer;
    std::stringstream ss(input);
    std::string temp;

    while (std::getline(ss, temp, delimiter)) {
        answer.push_back(temp);
    }

    return (answer);
}

long stol(std::string str)
{
    std::stringstream	ss_long(str);
    long 				tmp = 0;
	long				result = 0;

	while (ss_long >> tmp) 
	{
		result *= 10;
		result += tmp;
	}
    return result;
}

std::string ltos(long val)
{
	std::stringstream	ss;
	
	ss << val;
	return (ss.str());
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

std::string vec_str_join(std::vector<std::string> vec, std::string delim)
{
	std::vector<std::string>::iterator	iter = vec.begin();
	std::vector<std::string>::iterator	end = vec.end();
	std::string							result = "";

	for (; iter != end; iter++)
	{
		if (iter == vec.begin())
			result.append(*iter);
		else
		{
			result.append(delim);
			result.append(*iter);
		}
	}
	return (result);
}

} // ft
