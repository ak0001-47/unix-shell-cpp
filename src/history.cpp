#include "history.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

void History::add(const std::string& command)
{
    if (command.empty())
    {
        return;
    }

    commands.push_back(command);
}

void History::print() const
{
    for (size_t i = 0; i < commands.size(); ++i)
    {
        std::cout << i + 1 << "  " << commands[i] << '\n';
    }
}

void History::load()
{
    const char* home = std::getenv("HOME");

    if (home == nullptr)
    {
        return;
    }

    history_file = std::string(home) + "/.mysh_history";

    std::ifstream file(history_file);

    if (!file.is_open())
    {
        return;
    }

    std::string command;

    while (std::getline(file, command))
    {
        if (!command.empty())
        {
            commands.push_back(command);
        }
    }
}

void History::save() const
{
    if (history_file.empty())
    {
        return;
    }

    std::ofstream file(history_file);

    if (!file.is_open())
    {
        std::cerr << "mysh: unable to save history\n";
        return;
    }

    for (const auto& command : commands)
    {
        file << command << '\n';
    }
}