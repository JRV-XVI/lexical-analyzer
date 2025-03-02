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
  Automata() {
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
      start->addTransition(symbol, operators);
    }
  }

  std::vector<std::string> analize(std::string input) {
    std::vector<std::string> values;
    std::string word;
    Node *currentNode = start;
    for (char symbol : input) {
      std::string strSymbol(1, symbol);
      Node *nextNode = currentNode->getNextNode(strSymbol);
      if (nextNode != nullptr) {
        currentNode = nextNode;
        word.push_back(symbol);
      } else if (currentNode->isFinal) {
        if (!word.empty()) {
          values.push_back(word);
        }
        word.clear();
        currentNode = start;
        if (currentNode->getNextNode(strSymbol) != nullptr) {
          word.push_back(symbol);
          currentNode = currentNode->getNextNode(strSymbol);
        }
      }
    }

    if (!word.empty() && currentNode->isFinal) {
      values.push_back(word);
    }
    return values;
  }
};

#endif
