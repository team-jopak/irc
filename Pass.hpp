#ifndef PASS_HPP
# define PASS_HPP

#include "Command.hpp"

class Pass : public Command
{
public:
    Pass() : Command("PASS")
    {
    }

    virtual void parse_args(str_vec_iter begin, str_vec_iter end)
    {
        std::cout << "args : ";

        for (; begin != end; begin++)
        {
            std::cout << *begin << " ";
        }
        std::cout << "\n";
    }

    virtual void execute(Server server)
    {
        std::cout << "Execute PASS" << std::endl;
        init_cmd();
    }

    virtual void init_cmd()
    {
        std::cout << "Init command" << std::endl;
    }

};

#endif