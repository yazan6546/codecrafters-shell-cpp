#include "builtin_commands.h"
#include "path_utils.h"
#include <iostream>
#include <filesystem>

builtin_commands::builtin_commands() {
    // Initialize set of built-in commands
    commands = {"exit", "echo", "type", "pwd", "cd"};
}

bool builtin_commands::is_builtin(const std::string& command) {
    return commands.contains(command);
}

void builtin_commands::handle_command(const std::string& command, 
                                     const std::string& args, 
                                     bool& running) {
    if (command == "exit") {
        running = false;
        exit(0);
    }
    if (command == "echo") {
        std::cout << args << std::endl;
    } else if (command == "type") {
        if (is_builtin(args)) {
            std::cout << args << " is a shell builtin" << std::endl;
        } else {
            std::string path = path_utils::search_paths(
                path_utils::get_env("PATH"), args);
            
            if (path.empty()) {
                std::cout << args << ": not found" << std::endl;
            } else {
                std::cout << args << " is " << path << std::endl;
            }
        }
    } else if (command == "pwd") {
        std::cout << std::filesystem::current_path().string() << std::endl;
    }
    if (command == "cd") {
        
    }
}
