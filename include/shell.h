#pragma once
#include <string>

#include "builtin_commands.h"

class shell {
private:
    std::string prompt;
    bool running;
    builtin_commands commands;

public:
    shell(std::string  prompt = "$ ");
    void run();
    void process_input(const std::string& input);
};
