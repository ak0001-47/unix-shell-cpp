#include "shell.hpp"

#include <iostream>

void Shell::print_prompt()
{
    std::cout << "mysh> " << std::flush;
}

void Shell::run()
{
    print_prompt();
}