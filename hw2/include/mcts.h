#pragma once

#include <array>
#include <memory>

#include "poker.h"

#define MAX_CHILDREN 5

namespace mcts {

enum Action {
  HIT,
  STAND,
  DOUBLE,
  SURRENDER,
  INSURANCE,
};

enum Result {
  WIN,
  LOSE,
  DRAW,
};

class Node {
 public:
  std::shared_ptr<Node> parent;

  std::array<std::shared_ptr<Node>, MAX_CHILDREN> children;

  int wins;

  int visits;

  int point;

  Action action;
  Result result;

  std::vector<Poker> pokers;
  std::vector<Poker> bankerPokers;

  double getUCBValue() const;
};

class MCTS {
 public:
  MCTS(int simualtions) : _simulations(simualtions) {};

  std::shared_ptr<Node> selection(std::shared_ptr<Node> root);

  void expansion(std::shared_ptr<Node> node);

  void playout(std::shared_ptr<Node> node);

  void backpropagation(std::shared_ptr<Node> node, int result);
  std::shared_ptr<Node> getBestNode(std::shared_ptr<Node> root);

 private:
  int _simulations;
};
}  // namespace mcts