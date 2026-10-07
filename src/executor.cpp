#include "executor.hpp"

#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t Executor::execute(const Command& command, bool background)
{
   if (command.program.empty())
   {
     return -1;
   }

    pid_t pid = fork();

    if (pid < 0)
    {
        std::cerr << "mysh: fork failed\n";
        return -1;
    }

    if (pid == 0)
    {
        if (background)
   {
     setpgid(0, 0);
   }
       
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

    if (background)
{
    std::cout << "[background] pid: " << pid << '\n';
}
else
{
    int status;

    if (waitpid(pid, &status, 0) < 0)
    {
        std::cerr << "mysh: waitpid failed\n";
    }
}

   return pid;
}

void Executor::execute_pipeline(const Pipeline& pipeline)
{
    if (pipeline.commands.size() < 2)
    {
        return;
    }

    int previous_read_fd = -1;

    std::vector<pid_t> child_pids;

    pid_t pgid = 0;

    for (size_t i = 0; i < pipeline.commands.size(); ++i)
    {
        int pipe_fd[2] = {-1, -1};

        bool has_next_command = (i < pipeline.commands.size() - 1);

        if (has_next_command)
        {
            if (pipe(pipe_fd) < 0)
            {
                perror("mysh: pipe");
                return;
            }
        }

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("mysh: fork");
            return;
        }

        if (pid == 0)
        {
            if (pgid == 0)
           {
               setpgid(0, 0);
            }
            else
            {
                setpgid(0, pgid);
           }

            // Connect previous command's output to stdin.
            if (previous_read_fd != -1)
            {
                if (dup2(previous_read_fd, STDIN_FILENO) < 0)
                {
                    perror("mysh: dup2");
                    _exit(1);
                }
            }

            // Connect stdout to the next pipe.
            if (has_next_command)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
                {
                    perror("mysh: dup2");
                    _exit(1);
                }
            }

            if (previous_read_fd != -1)
            {
                close(previous_read_fd);
            }

            if (has_next_command)
            {
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            const Command& command = pipeline.commands[i];

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

        if (pgid == 0)
         {
             pgid = pid;
         }

         setpgid(pid, pgid);

         child_pids.push_back(pid);

         if (previous_read_fd != -1)
        {
            close(previous_read_fd);
        }

        if (has_next_command)
        {
            close(pipe_fd[1]);
            previous_read_fd = pipe_fd[0];
        }
        else
        {
            previous_read_fd = -1;
        }
    }

    if (pipeline.background)
{
    std::cout << "[background]";

    for (pid_t pid : child_pids)
    {
        std::cout << " " << pid;
    }

    std::cout << '\n';
}
else
{
    for (pid_t pid : child_pids)
    {
        waitpid(pid, nullptr, 0);
    }
}
}