#include "command_executor.h"
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#include "command_parser.h"

void command_executor::execute_command(const std::string& command, const std::string& args) {
    pid_t pid = fork();

    char** list = command_parser::get_list_of_args(command, args);

    if (pid == 0) {
        execvp(command.c_str(), list);
        perror("execvp");
        exit(1);
    }

    waitpid(pid, nullptr, 0);

    // Free memory
    for (int i = 0; list[i] != nullptr; i++) {
        free(list[i]);
    }
    delete[] list;
}
