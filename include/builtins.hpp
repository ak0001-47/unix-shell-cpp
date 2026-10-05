#ifndef MYSH_BUILTINS_HPP
#define MYSH_BUILTINS_HPP

#include "parser.hpp"

class Builtins
{
public:
    bool is_builtin(const Command& command);
    bool execute(const Command& command);
};

#endif