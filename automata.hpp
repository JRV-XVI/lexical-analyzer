#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include "node.hpp"
#include <iostream>

class Automata {
public:
  Node *node;

  Automata(Node &node) { this->node = &node; }

  bool validation(std::string word) {
    bool result = false;
    if (word.empty() || word == "") {
      if (node->isFinal) {
        return true;
      } else {
        return false;
      }
    }
    Node *currentNode = node;
    for (unsigned i = 0; i < word.length(); ++i) {
      std::string symbol = word.substr(i, i + 1);
      std::cout << symbol << std::endl;
      *currentNode = currentNode->getNextNode(symbol);
      if (currentNode == nullptr) {
        return false;
      }
      if (currentNode->isFinal) {
        result = true;
      } else {
        result = false;
      }
    }
    return result;
  }
};

#endif
