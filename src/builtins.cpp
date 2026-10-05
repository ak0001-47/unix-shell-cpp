#include "builtins.hpp"

#include <cstdlib>
#include <iostream>
#include <unistd.h>

bool Builtins::is_builtin(const Command& command)
{
    if (command.program == "cd")
        return true;

    if (command.program == "pwd")
        return true;

    if (command.program == "exit")
        return true;

    if (command.program == "help")
        return true;

    return false;
}

bool Builtins::execute(const Command& command)
{
    if (command.program == "cd")
    {
        const char* path = nullptr;

        if (command.arguments.size() == 1)
        {
            path = std::getenv("HOME");

            if (path == nullptr)
            {
                std::cerr << "mysh: HOME not set\n";
                return true;
            }
        }
        else if (command.arguments.size() == 2)
        {
            path = command.arguments[1].c_str();
        }
        else
        {
            std::cerr << "mysh: cd: too many arguments\n";
            return true;
        }

        if (chdir(path) != 0)
        {
            std::perror("mysh: cd");
        }

        return true;
    }

    if (command.program == "pwd")
    {
        char buffer[4096];

        if (getcwd(buffer, sizeof(buffer)) != nullptr)
        {
            std::cout << buffer << '\n';
        }
        else
        {
            std::perror("mysh: pwd");
        }

        return true;
    }

    if (command.program == "exit")
    {
        return true;
    }

    if (command.program == "help")
    {
        std::cout << "mysh - a Unix-like shell written in C++\n\n";

        std::cout << "Built-in commands:\n";
        std::cout << "  cd [directory]   Change directory\n";
        std::cout << "  pwd              Print current directory\n";
        std::cout << "  exit             Exit the shell\n";
        std::cout << "  help             Show this help message\n";

        return true;
    }

    return false;
}