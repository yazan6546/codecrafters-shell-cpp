#include "command_executor.h"
#include <sstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

void command_executor::execute_command(const std::string& command, const std::string& args) {
    pid_t pid = fork();

    char** list = get_list_of_args(command, args);

    if (pid == 0) {
        execvp(command.c_str(), list);
        perror("execvp");
        exit(1);
    } else {
        waitpid(pid, nullptr, 0);
    }

    // Free memory
    for (int i = 0; list[i] != nullptr; i++) {
        free(list[i]);
    }
    delete[] list;
}

char** command_executor::get_list_of_args(const std::string& command, const std::string& args) {
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