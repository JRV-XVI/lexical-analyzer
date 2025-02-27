#ifndef NODE_HPP
#define NODE_HPP

#include <map>
#include <ostream>
#include <string>

class Node {
public:
  // Atributes
  std::string name;
  bool isFinal;
  bool isDeathState;
  std::map<std::string, Node> transition;

  // Methods
  Node() = default;

  Node(std::string name, bool isFinal, bool isDeathState) {
    this->name = name;
    this->isFinal = isFinal;
    this->isDeathState = isDeathState;
  }

  void addTransition(std::string symbol, Node node) {
    transition[symbol] = node;
  }
  Node getNextNode(const std::string symbol) { return transition.at(symbol); }

  friend std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "{" << node.name << node.isFinal << node.isDeathState << "}";
    return os;
  }
};

#endif
