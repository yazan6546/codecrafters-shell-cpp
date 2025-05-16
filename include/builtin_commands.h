#pragma once
#include <string>
#include <unordered_set>

class builtin_commands {
private:
    std::unordered_set<std::string> commands;

public:
    builtin_commands();
    bool is_builtin(const std::string& command);
    void handle_command(const std::string& command, const std::string& args, bool& running);
};