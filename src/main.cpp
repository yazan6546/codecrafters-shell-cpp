#include <iostream>
#include <regex>
#include <string>

std::string trim(const std::string &str);
std::string extract_command(const std::string& input);
bool is_valid(const std::string& input);
std::string extract_args(const std::string& input);
void handle_command(const std::string& command, const std::string& args);

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

    if (!is_valid(command)) {
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

bool is_valid(const std::string& input) {

  // Remove leading whitespaces
  if (input == "exit" || input == "echo" || input == "type") {
    return true;
  }
  return false;
}


// std::string trim(const std::string &str) {
//   std::string output = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
//   // delete str;
//   return output;
// }

void handle_command(const std::string& command, const std::string& args) {
  if (command == "exit") {
    exit(0);
  }

  if (command == "echo") {
    std::cout << args << std::endl;
    return;
  }


  if (command == "type" && is_valid(args)) {
    std::cout << args << " is a shell builtin" << std::endl;
    return;
  }
  if (command == "type" && !is_valid(args)) {
    std::cout << args <<": not found" << std::endl;
  }
}
