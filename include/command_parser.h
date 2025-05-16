#pragma once
#include <string>

namespace command_parser {
    std::string extract_command(const std::string& input);
    std::string extract_args(const std::string& input);
    char** get_list_of_args(const std::string& command, const std::string& args);

};