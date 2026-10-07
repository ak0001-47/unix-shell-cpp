#ifndef MYSH_SHELL_HPP
#define MYSH_SHELL_HPP

#include "builtins.hpp"
#include "executor.hpp"
#include "parser.hpp"
#include "history.hpp"
#include "jobs.hpp"

#include <string>

class Shell
{
public:
    void run();

private:
    void print_prompt();
    std::string read_command();

    Parser parser;
    Executor executor;
    Builtins builtins;
    History history;
    JobManager job_manager;
};

#endif