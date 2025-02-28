#ifndef NODE_HPP
#define NODE_HPP

#include <unordered_map>
#include <ostream>
#include <string>

class Node {
public:
  // Atributes
  std::string name;
  bool isFinal;
  bool isDeathState;
  std::unordered_map<std::string, Node *> transition;

  // Methods
  Node() = default;

  Node(std::string name, bool isFinal, bool isDeathState)
      : name(name), isFinal(isFinal), isDeathState(isDeathState) {}

  void addTransition(const std::string &symbol, Node *node) {
    transition[symbol] = node;
  }
  Node *getNextNode(const std::string &symbol) {
    if (transition.find(symbol) != transition.end()) {
      return transition[symbol];
    }
    return nullptr;
  }

  friend std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "{" << node.name << node.isFinal << node.isDeathState << "}";
    return os;
  }
};

#endif
