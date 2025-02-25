#include "mcts.h"

std::shared_ptr<mcts::Node> mcts::MCTS::selection(std::shared_ptr<Node> root) {
  std::shared_ptr<Node> node = root;
  while (!node->children.empty()) {
    double maxUCB = -1;
    std::shared_ptr<Node> bestChild;
    for (const auto& child : node->children) {
      double ucbValue = child->getUCBValue();
      if (ucbValue > maxUCB) {
        maxUCB = ucbValue;
        bestChild = child;
      }
    }
    node = bestChild;
  }
  return node;
}