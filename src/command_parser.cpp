#include "command_parser.h"
#include <string>

std::string command_parser::extract_command(const std::string& input) {
    std::string output = input.substr(0, input.find_first_of(' '));
    std::string ltrimmed = output.substr(output.find_first_not_of(' '));
    
    return ltrimmed;
}

std::string command_parser::extract_args(const std::string& input) {
    int pos = input.find_first_of(' ');
    if (pos == std::string::npos) {
        return "";
    }
    const std::string output = input.substr(pos);
    pos = output.find_first_not_of(' ');
    if (pos == std::string::npos) {
        return "";
    }
    std::string ltrimmed = output.substr(pos);
    return ltrimmed;
}