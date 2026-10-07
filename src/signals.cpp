#include "signals.hpp"

#include <csignal>
#include <sys/wait.h>
#include <unistd.h>

void SignalHandler::setup()
{
    struct sigaction sigchld_action{};
    sigchld_action.sa_handler = handle_sigchld;
    sigemptyset(&sigchld_action.sa_mask);
    sigchld_action.sa_flags = SA_RESTART;

    sigaction(SIGCHLD, &sigchld_action, nullptr);

    struct sigaction sigint_action{};
    sigint_action.sa_handler = handle_sigint;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sigint_action, nullptr);
}

void SignalHandler::handle_sigchld(int)
{
    while (waitpid(-1, nullptr, WNOHANG) > 0)
    {
    }
}

void SignalHandler::handle_sigint(int)
{
    const char message[] = "\n";
    write(STDOUT_FILENO, message, sizeof(message) - 1);
}