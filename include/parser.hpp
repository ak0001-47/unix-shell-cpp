#ifndef MYSH_PARSER_HPP
#define MYSH_PARSER_HPP

#include <string>
#include <vector>

struct Command
{
    std::string program;
    std::vector<std::string> arguments;
};

class Parser
{
public:
    Command parse(const std::string& input);
};

#endif