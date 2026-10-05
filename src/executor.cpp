#include "executor.hpp"

#include <fcntl.h>
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
        // Input redirection: <
        if (!command.input_file.empty())
        {
            int input_fd = open(command.input_file.c_str(), O_RDONLY);

            if (input_fd < 0)
            {
                perror("mysh: input");
                _exit(1);
            }

            if (dup2(input_fd, STDIN_FILENO) < 0)
            {
                perror("mysh: dup2");
                close(input_fd);
                _exit(1);
            }

            close(input_fd);
        }

        // Output redirection: > or >>
        if (!command.output_file.empty())
        {
            int flags = O_WRONLY | O_CREAT;

            if (command.append_output)
            {
                flags |= O_APPEND;
            }
            else
            {
                flags |= O_TRUNC;
            }

            int output_fd = open(
                command.output_file.c_str(),
                flags,
                0644
            );

            if (output_fd < 0)
            {
                perror("mysh: output");
                _exit(1);
            }

            if (dup2(output_fd, STDOUT_FILENO) < 0)
            {
                perror("mysh: dup2");
                close(output_fd);
                _exit(1);
            }

            close(output_fd);
        }

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