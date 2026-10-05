#include "parser.hpp"

#include <sstream>

Command Parser::parse_command(const std::string& input)
{
    Command command;

    std::istringstream stream(input);
    std::string token;

    while (stream >> token)
    {
        if (token == ">")
        {
            if (stream >> command.output_file)
            {
                command.append_output = false;
            }

            continue;
        }

        if (token == ">>")
        {
            if (stream >> command.output_file)
            {
                command.append_output = true;
            }

            continue;
        }

        if (token == "<")
        {
            stream >> command.input_file;
            continue;
        }

        command.arguments.push_back(token);
    }

    if (!command.arguments.empty())
    {
        command.program = command.arguments[0];
    }

    return command;
}

Pipeline Parser::parse(const std::string& input)
{
    Pipeline pipeline;

    std::stringstream stream(input);
    std::string command_text;

    while (std::getline(stream, command_text, '|'))
    {
        if (!command_text.empty())
        {
            pipeline.commands.push_back(
                parse_command(command_text)
            );
        }
    }

    return pipeline;
}