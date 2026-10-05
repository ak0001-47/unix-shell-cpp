#include "parser.hpp"

#include <sstream>

Command Parser::parse(const std::string& input)
{
    Command command;

    std::istringstream stream(input);
    std::string token;

    while (stream >> token)
    {
        command.arguments.push_back(token);
    }

    if (!command.arguments.empty())
    {
        command.program = command.arguments[0];
    }

    return command;
}