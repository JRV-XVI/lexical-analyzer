#include "automata.hpp"
#include "node.hpp"
#include <iostream>

int main() {
  Node S("S", false, false);
  Node B("B", false, true);
  Node BB("BB", true, false);

  S.addTransition("a", &S);
  S.addTransition("b", &B);
  B.addTransition("a", &S);
  B.addTransition("b", &BB);
  BB.addTransition("a", &BB);
  BB.addTransition("b", &BB);

  std::cout << S << std::endl;
  std::cout << B << std::endl;
  std::cout << BB << std::endl;
  std::cout << B.transition["a"] << std::endl;

  Automata automaton(S);

  std::string word = "abb";
  bool res = automaton.validation(word);

  std::cout << res << std::endl;
}
