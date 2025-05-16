#pragma once
#include <string>

namespace command_parser {
    std::string extract_command(const std::string& input);
    std::string extract_args(const std::string& input);
};