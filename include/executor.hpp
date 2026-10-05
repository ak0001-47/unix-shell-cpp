#ifndef MYSH_EXECUTOR_HPP
#define MYSH_EXECUTOR_HPP

#include "parser.hpp"

class Executor
{
public:
    void execute(const Command& command);
};

#endif