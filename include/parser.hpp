#ifndef MYSH_PARSER_HPP
#define MYSH_PARSER_HPP

#include <string>
#include <vector>

struct Command
{
    std::string program;
    std::vector<std::string> arguments;

    std::string input_file;
    std::string output_file;

    bool append_output = false;
};

class Parser
{
public:
    Command parse(const std::string& input);
};

#endif