#ifndef MYSH_PARSER_HPP
#define MYSH_PARSER_HPP

#include <string>
#include <vector>

struct Token
{
    std::string value;
    bool operator_token = false;
};

struct Command
{
    std::string program;
    std::vector<std::string> arguments;

    std::string input_file;
    std::string output_file;

    bool append_output = false;
};

struct Pipeline
{
    std::vector<Command> commands;
    bool background = false;
};

class Parser
{
public:
    Pipeline parse(const std::string& input);

private:
    std::vector<Token> tokenize(const std::string& input, bool& valid);
    Command parse_command(const std::vector<Token>& tokens);

    std::string expand_variables(const std::string& input,bool allow_expansion);
};

#endif