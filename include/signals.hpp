#ifndef MYSH_SIGNALS_HPP
#define MYSH_SIGNALS_HPP

class SignalHandler
{
public:
    static void setup();

private:
    static void handle_sigchld(int signal);
    static void handle_sigint(int signal);
};

#endif