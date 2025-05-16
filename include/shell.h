#pragma once
#include <filesystem>
#include <string>

#include "builtin_commands.h"

class shell {
private:
    std::string prompt;
    bool running;
    builtin_commands commands;
    std::filesystem::path current_path;

public:
    shell();
    void run();
    void process_input(const std::string& input);
};
