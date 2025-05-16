#pragma once
#include <string>

namespace command_executor {
    void execute_command(const std::string& command, const std::string& args);
    char** get_list_of_args(const std::string& command, const std::string& args);
};