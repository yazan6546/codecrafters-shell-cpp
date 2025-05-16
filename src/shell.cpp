#include "shell.h"
#include <iostream>
#include <utility>
#include "path_utils.h"

#include "builtin_commands.h"
#include "command_executor.h"
#include "command_parser.h"


shell::shell() : prompt(std::filesystem::current_path().string() + "$ "), running(true) {
    // Flush after every std::cout / std::cerr
    builtin_commands builtin_commands;
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
}

void shell::run() {
    std::string input;

    while (running) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        process_input(input);
    }
}

void shell::process_input(const std::string& input) {

    std::string command_name = command_parser::extract_command(input);
    std::string args = command_parser::extract_args(input);
    
    if (commands.is_builtin(command_name)) {
        commands.handle_command(command_name, args, running);
    } else {
        std::string path = path_utils::search_paths(
            path_utils::get_env("PATH"), command_name);
        
        if (!path.empty()) {
            command_executor::execute_command(command_name, args);
        } else {
            std::cout << command_name << ": not found" << std::endl;
        }
    }
}