#ifndef MYSH_BUILTINS_HPP
#define MYSH_BUILTINS_HPP

#include "history.hpp"
#include "parser.hpp"
#include "jobs.hpp"

class Builtins
{
public:
    bool is_builtin(const Command& command);
    bool execute(const Command& command, History& history, JobManager& job_manager);
};

#endif