#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  // Uncomment this block to pass the first stage
  std::cout << "$ ";

  std::getline(std::cin, input);

  std::cout << input << ": command not found" << std::endl;

}
