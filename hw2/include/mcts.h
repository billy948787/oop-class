#pragma once

#include <array>
#include <memory>

#define MAX_CHILDREN 5

namespace mcts {
class Tree {};

class Node {
 public:
  std::shared_ptr<Node> parent;

  std::array<std::shared_ptr<Node>, MAX_CHILDREN> children;
};
}  // namespace mcts