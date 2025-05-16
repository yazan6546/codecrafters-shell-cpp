#include <iostream>
#include <regex>
#include <string>
#include <cstdlib>
#include <filesystem>

std::string trim(const std::string &str);
std::string extract_command(const std::string& input);
bool is_builtin(const std::string& input);
std::string extract_args(const std::string& input);
void handle_command(const std::string& command, const std::string& args);
std::string get_env(const std::string &key);
std::string search_paths(const std::string &paths, const std::string &command);

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

    if (!is_builtin(command)) {
      std::cout << command <<": not found" << std::endl;
      continue;
    }

    std::string args = extract_args(input);
    handle_command(command, args);

  }
}


std::string extract_command(const std::string& input) {
  std::string output = input.substr(0, input.find_first_of(' '));
  std::string ltrimmed = output.substr(output.find_first_not_of(' '));

  return ltrimmed;
}

std::string extract_args(const std::string& input) {
  std::string output = input.substr(input.find_first_of(' '));
  std::string ltrimmed = output.substr(output.find_first_not_of(' '));
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
    if (path.filename() == command) {
      return path;
    }
  }
  return "";

}