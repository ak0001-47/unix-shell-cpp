#ifndef MYSH_SHELL_HPP
#define MYSH_SHELL_HPP

#include <string>

class Shell
{
public:
    void run();

private:
    void print_prompt();
    std::string read_command();
};

#endif