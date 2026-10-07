#ifndef MYSH_EXECUTOR_HPP
#define MYSH_EXECUTOR_HPP

#include "parser.hpp"

class Executor
{
public:
    void execute(const Command& command, bool background = false);
    void execute_pipeline(const Pipeline& pipeline);
};

#endif