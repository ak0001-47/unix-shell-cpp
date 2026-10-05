#include "shell.hpp"

#include <iostream>
#include <string>

void Shell::print_prompt()
{
    std::cout << "mysh> " << std::flush;
}

std::string Shell::read_command()
{
    std::string command;

    if (!std::getline(std::cin, command))
    {
        std::cout << '\n';
        return "exit";
    }

    return command;
}

void Shell::run()
{
    while (true)
    {
        print_prompt();

        std::string command = read_command();

        if (command.empty())
        {
            continue;
        }

        std::cout << "You entered: " << command << '\n';
    }
}