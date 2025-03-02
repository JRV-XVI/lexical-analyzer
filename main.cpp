#include "automata.hpp"
//#include "utilities.hpp"
#include <iostream>
#include <vector>

int main() {
  Automata system;
  std::string input = "tmp=32.4*(-8.6-b)/6.1";
  std::vector<std::string> values = system.analize(input);
  for (unsigned i = 0; i < values.size(); ++i) {
     std::cout << values.at(i) << std::endl;
  }
  // lexer("expressions.txt");

}
