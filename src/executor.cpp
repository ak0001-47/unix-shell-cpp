#include "executor.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void Executor::execute(const Command& command)
{
    if (command.program.empty())
    {
        return;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "mysh: fork failed\n";
        return;
    }

    if (pid == 0)
    {
        std::vector<char*> args;

        for (const auto& argument : command.arguments)
        {
            args.push_back(const_cast<char*>(argument.c_str()));
        }

        args.push_back(nullptr);

        execvp(command.program.c_str(), args.data());

        std::cerr << "mysh: command not found: "
                  << command.program << '\n';

        _exit(127);
    }

    int status;

    if (waitpid(pid, &status, 0) < 0)
    {
        std::cerr << "mysh: waitpid failed\n";
    }
}