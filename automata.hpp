#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include "node.hpp"
#include <array>
#include <string>
#include <unordered_map>
#include <vector>

class Automata {
private:
  Node *start = new Node("start", false, false);
  Node *integer = new Node("integer", true, false);
  Node *decimal = new Node("decimal", true, false);
  Node *variable = new Node("variable", true, false);
  Node *operators = new Node("operator", true, false);
  Node *parenthesis = new Node("parenthesis", true, false);
  Node *error = new Node("error", false, true);
  std::array<char, 5> operatorSymbols{'=', '+', '-', '*', '/'};
  std::unordered_map<std::string, std::string> types;

public:
  Automata(){
    // Initiaization
    types["integer"] = "integer";
    types["decimal"] = "float";
    types["variables"] = "variables";
    types["operators"] = "operators";
    types["parenthesis"] = "parenthesis";

    // Transitions
    start->addTransition(".", error);
    start->addTransition("(", parenthesis);
    start->addTransition(")", parenthesis);
    integer->addTransition(".", decimal);

    for (char c = '0'; c <= '9'; ++c) {
      std::string symbol(1, c);
      start->addTransition(symbol, integer);
      integer->addTransition(symbol, integer);
      decimal->addTransition(symbol, decimal);
    }

    for (char c = 'a'; c <= 'z'; ++c) {
      std::string symbol(1, c);
      start->addTransition(symbol, variable);
      variable->addTransition(symbol, variable);
    }

    for (char c : operatorSymbols) {
      std::string symbol(1, c);
      start->addTransition(symbol, variable);
    }
  }

  std::vector<std::string> analize(std::string input) {
    std::vector<std::string> tokens;
    std::string word;
    Node *currentNode = start;
    for (unsigned i = 0; i < input.length(); ++i) {
      char symbol = input[i];

      if (currentNode->getNextNode(std::string(1, symbol)) != nullptr) {
        currentNode = currentNode->getNextNode(std::string(1, symbol));
        word.push_back(symbol);
      } else {
        if (currentNode->isFinal) {
          tokens.push_back(std::string(1, symbol));
          word = "";
          currentNode = start;
          continue;
        } else {
          tokens.push_back("Error");
          word = "";
          currentNode = start;
        }
      }
    }
    return tokens;
  }
};

#endif
