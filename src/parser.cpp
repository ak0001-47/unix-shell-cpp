#include "parser.hpp"

#include <cstdlib>
#include <sstream>

std::string expand_variable(const std::string& token)
{
    if (token.size() < 2 || token[0] != '$')
    {
        return token;
    }

    std::string variable_name = token.substr(1);

    const char* value = std::getenv(variable_name.c_str());

    if (value == nullptr)
    {
        return "";
    }

    return value;
}

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

        command.arguments.push_back(expand_variable(token));
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
    std::string command_line = input;

    size_t pos = command_line.find_last_not_of(" \t");

    if (pos != std::string::npos && command_line[pos] == '&')
    {
        pipeline.background = true;
        command_line.erase(pos);

        pos = command_line.find_last_not_of(" \t");

        if (pos != std::string::npos)
        {
            command_line.erase(pos + 1);
        }
    }

    std::stringstream stream(command_line);
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