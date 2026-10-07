#ifndef MYSH_EXECUTOR_HPP
#define MYSH_EXECUTOR_HPP

#include "parser.hpp"
#include <sys/types.h>

class Executor
{
public:
    pid_t execute(const Command& command,bool background = false);
    void execute_pipeline(const Pipeline& pipeline);
};

#endif