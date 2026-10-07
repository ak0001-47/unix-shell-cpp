#include "shell.hpp"
#include "signals.hpp"

int main()
{
    SignalHandler::setup();

    Shell shell;
    shell.run();

    return 0;
}
