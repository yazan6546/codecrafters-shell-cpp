#include <iostream>
#include <regex>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

std::string trim(const std::string &str);
std::string extract_command(const std::string& input);
bool is_builtin(const std::string& input);
std::string extract_args(const std::string& input);
void handle_command(const std::string& command, const std::string& args);
std::string get_env(const std::string &key);
std::string search_paths(const std::string &paths, const std::string &command);
char** get_list_of_args(const std::string& args);
void execute_command(const std::string& command, const std::string& args);

[[noreturn]] int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  // Uncomment this block to pass the first stage

  while (true) {

    std::cout << "$ ";

    std::getline(std::cin, input);

    // input = trim(input);
    if (input.empty()) {
      continue;
    }

    std::string command = extract_command(input);
    std::string args = extract_args(input);

    if (!is_builtin(command)) {
      execute_command(command, args);
      continue;
    }

    handle_command(command, args);

  }
}


std::string extract_command(const std::string& input) {
  std::string output = input.substr(0, input.find_first_of(' '));
  std::string ltrimmed = output.substr(output.find_first_not_of(' '));

  return ltrimmed;
}

std::string extract_args(const std::string& input) {

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

bool is_builtin(const std::string& input) {

  // Remove leading whitespaces
  if (input == "exit" || input == "echo" || input == "type") {
    return true;
  }
  return false;
}


void handle_command(const std::string& command, const std::string& args) {


  if (command == "exit") {
    exit(0);
  }

  if (command == "echo") {
    std::cout << args << std::endl;
    return;
  }


  if (command == "type" && is_builtin(args)) {
    std::cout << args << " is a shell builtin" << std::endl;
    return;
  }
  if (command == "type" && !is_builtin(args)) {
    const std::string paths = get_env("PATH");
    const std::string path = search_paths(paths, args);

    if (path.empty()) {
      std::cout << args <<": not found" << std::endl;
      return;
    }
    std::cout << args << " is " << path << std::endl;
  }
}


std::string get_env(const std::string &key) {
  const char *value = std::getenv(key.c_str());
  return std::string{value};
}

// Function that returns true if it matches, false if no match
std::string search_paths(const std::string &paths, const std::string &command) {

  std::stringstream stream(paths);
  std::string path_string;

  while (std::getline(stream, path_string, ':')) {
    std::filesystem::path path(path_string);
    if (std::filesystem::exists(path / command)) {
      return path / command;
    }
  }
  return "";

}

void execute_command(const std::string& command, const std::string& args) {
  pid_t pid = fork();

  char **list;
  if (args.empty()) {
    list = nullptr;
  }
  else {
    list = get_list_of_args(args);
  }

  if (pid == 0) {
    execvp(command.c_str(), list);
  }
  else {
    waitpid(pid, nullptr, 0);
  }



  if (list != nullptr) {
    for (int i = 0; list[i] != nullptr; i++) {
      free(list[i]);  // Free each string
    }
    delete[] list;
  }
}

char** get_list_of_args(const std::string& args) {
  std::vector<std::string> arg_parts;
  std::istringstream iss(args);
  std::string arg;

  while (iss >> arg) {
    arg_parts.push_back(arg);
  }

  char** array = new char*[arg_parts.size() + 1];
  for (size_t i = 0; i < arg_parts.size(); i++) {
    array[i] = strdup(arg_parts[i].c_str());
  }
  array[arg_parts.size()] = nullptr; // NULL terminator for execvp

  return array;
}