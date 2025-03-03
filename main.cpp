#include "automata.hpp"
#include "utilities.hpp"
#include <iostream>
#include <vector>

int main() {
  /*Automata system;
  std::string input = "tmp=32.4*(-8.6-b)/6.1";
  std::vector<std::pair<std::string, std::string>> values = system.analyze(input);
  for (unsigned i = 0; i < values.size(); ++i) {
     std::cout << values.at(i).first << ": " << values.at(i).second << std::endl;
  }*/
  
  lexer("expressions.txt");

}
