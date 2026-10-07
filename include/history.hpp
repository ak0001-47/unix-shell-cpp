#ifndef MYSH_HISTORY_HPP
#define MYSH_HISTORY_HPP

#include <string>
#include <vector>

class History
{
public:
    void add(const std::string& command);
    void print() const;

    void load();
    void save() const;

private:
    std::vector<std::string> commands;
    std::string history_file;
};

#endif