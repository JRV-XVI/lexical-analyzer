#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include "node.hpp"
#include <tuple>
#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Automata {
private:
  Node *start = new Node("start", false, false);
  Node *integer = new Node("integer", true, false);
  Node *decimal = new Node("decimal", true, false);
  Node *variable = new Node("variables", true, false);
  Node *operators = new Node("operator", true, false);
  Node *assigment = new Node("assigment", true, false);
  Node *sum = new Node("sum", true, false);
  Node *subtract = new Node("subtract", true, false);
  Node *product = new Node("product", true, false);
  Node *division = new Node("division", true, false);
  Node *parenthesis = new Node("parenthesis", true, false);
  Node *rightParentesis = new Node("rightParentesis", true, false);
  Node *leftParentesis = new Node("leftParentesis", true, false);
  Node *error = new Node("error", false, true);
  std::array<char, 5> operatorSymbols{'=', '+', '-', '*', '/'};
  std::unordered_map<std::string, std::string> types;

public:
  Automata() {
    // Initiaization
    types["integer"] = "integer";
    types["decimal"] = "float";
    types["variables"] = "variables";
    types["assigment"] = "assigment";
    types["sum"] = "sum";
    types["subtract"] = "subtract";
    types["product"] = "product";
    types["division"] = "division";
    types["rightParentesis"] = "right parentesis";
    types["leftParentesis"] = "left parentesis";

    // Transitions
    start->addTransition(".", error);
    start->addTransition("(", leftParentesis);
    start->addTransition(")", rightParentesis);
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
      if (c == '+') {
        start->addTransition(symbol, sum);
      } else if (c == '-') {
        start->addTransition(symbol, subtract);
      } else if (c == '*') {
        start->addTransition(symbol, product);
      } else if (c == '/') {
        start->addTransition(symbol, division);
      } else {
        start->addTransition(symbol, assigment);
      }
    }
  }
  
  // Analize string and checks if is valid on the automata
  std::vector<std::pair<std::string, std::string>> analize(std::string input) {
    std::vector<std::pair<std::string, std::string>> values;
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
          std::pair<std::string, std::string> wordValue = {word, types[currentNode->name]};
          values.push_back(wordValue);
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
      std::pair<std::string, std::string> wordValue= {word, types[currentNode->name]};
      values.push_back(wordValue);
    }
    return values;
  }
};

#endif
