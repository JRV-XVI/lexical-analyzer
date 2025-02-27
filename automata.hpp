#ifndef AUTOMATA_HPP
#define AUTOMATA_HPP

#include "node.hpp"
#include <iostream>

class Automata {
public:
  Node *node;

  Automata(Node &node) : node(&node) {}

  bool validation(std::string &word) {
    bool result = false;
    Node *currentNode = node;

    if (word.empty()) {
      return node->isFinal;
    }
    
    for (char character : word) {
      std::string symbol(1, character);
      std::cout << "New character..." << symbol << std::endl;
      currentNode = currentNode->getNextNode(symbol);
      if (currentNode == nullptr) {
        return false;
      }
      result = currentNode->isFinal ? true : false;
      std::cout << *currentNode << std::endl;
    }
    return result;
  }
};

#endif
