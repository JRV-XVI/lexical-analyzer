#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include "node.hpp"
#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Automata {
private:
  Node *start = new Node("start", false, false);
  Node *integer = new Node("integer", true, false);
  Node *decimal = new Node("float", true, false);
  Node *variable = new Node("variable", true, false);
  Node *assigment = new Node("assigment", true, false);
  Node *sum = new Node("sum", true, false);
  Node *subtract = new Node("subtract", true, false);
  Node *product = new Node("product", true, false);
  Node *division = new Node("division", true, false);
  Node *rightParentesis = new Node("right parentesis", true, false);
  Node *leftParentesis = new Node("left parentesis", true, false);
  std::array<char, 5> operatorSymbols{'=', '+', '-', '*', '/'};
  std::unordered_map<std::string, std::string> types;

public:
  Automata() {
    // Transitions
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

  // Analyze string and checks if is valid on the automata
  std::vector<std::pair<std::string, std::string>> analyze(std::string input) {
    std::vector<std::pair<std::string, std::string>>
        values; // vector to store the final result
    std::string
        word; // variable that accumulates characters to complete a string
    Node *currentNode = start; // pointer to keep track of the current state
    for (char symbol : input) {
      std::string strSymbol(
          1, symbol); // convert the current character (symbol) to string
      Node *nextNode = currentNode->getNextNode(
          strSymbol); // find next state from the current node
      if (nextNode != nullptr) {
        currentNode = nextNode; // update the current node to next node
        word.push_back(symbol); // append the current symbol to 'word' string
      } else if (currentNode->isFinal) {
        if (!word.empty()) {
          std::pair<std::string, std::string> wordValue = {
              word, currentNode->name}; // pair that contains the
                                        // accumulated word and its type
          values.push_back(wordValue);  // add the pair to the values vector
        }
        word.clear(); // clear the 'word' string
        currentNode =
            start; // reset current node to the start node (initial state)
        nextNode = currentNode->getNextNode(
            strSymbol); // point to next node from new reseted current node
        if (nextNode != nullptr) { // if there's a valid transition from the
                                   // start node with the current symbol:
          word.push_back(symbol);  // update word
          currentNode =
              currentNode->getNextNode(strSymbol); // update current node
        }
      }
    }

    if (!word.empty() &&
        currentNode->isFinal) { // check if anything remains in 'word' and if
                                // the current node is a final state
      std::pair<std::string, std::string> wordValue = {
          word, currentNode->name}; // pair with the remaining 'word' and
                                    // its type
      values.push_back(wordValue);  // add the pair to values
    }
    return values;
  }
};

#endif
