#include <iostream>
#include <regex>
#include <string>

[[noreturn]] int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  // Uncomment this block to pass the first stage

  while (true) {

    std::cout << "$ ";

    std::getline(std::cin, input);
    if (std::regex_match(input, std::regex("^exit [0-9]+$"))) {
      return 0;
    }

    std::cout << input << ": command not found" << std::endl;

  }
}
