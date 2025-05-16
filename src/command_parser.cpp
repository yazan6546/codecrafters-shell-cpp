#include "command_parser.h"

#include <cstring>
#include <sstream>
#include <vector>

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

char** command_parser::get_list_of_args(const std::string& command, const std::string& args) {
    std::vector<std::string> arg_parts;
    arg_parts.push_back(command);  // First argument is the command itself

    std::istringstream iss(args);
    std::string arg;
    while (iss >> arg) {
        arg_parts.push_back(arg);
    }

    char** array = new char*[arg_parts.size() + 1];
    for (size_t i = 0; i < arg_parts.size(); i++) {
        array[i] = strdup(arg_parts[i].c_str());
    }
    array[arg_parts.size()] = nullptr;  // NULL terminator

    return array;
}