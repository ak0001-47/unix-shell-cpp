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

        std::string input = read_command();

        if (input.empty())
        {
            continue;
        }

        Pipeline pipeline = parser.parse(input);

        if (pipeline.commands.empty())
        {
            continue;
        }

        if (pipeline.commands.size() == 1)
{
    Command& command = pipeline.commands[0];

    if (builtins.is_builtin(command))
    {
        if (command.program == "exit")
        {
            break;
        }

        builtins.execute(command);
        continue;
    }

    executor.execute(command);
}
else
{
    executor.execute_pipeline(pipeline);
}
    }
}