#include "mcts.h"

mcts::MCTS::MCTS(int simualtions, std::vector<Poker> knownCardPool,
                 std::vector<Poker> dealerVisibleCards)
    : _simulations(simualtions),
      _knownCardPool(knownCardPool),
      _dealerVisibleCards(dealerVisibleCards) {}

void mcts::MCTS::run() { auto root = std::make_shared<Node>(); }

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

double mcts::Node::getUCBValue() const {
  if (visits == 0) return std::numeric_limits<double>::max();

  const double explorationConstant = 1.414;

  return static_cast<double>(wins) / visits +
         explorationConstant * sqrt(log(parent->visits) / visits);
}

void mcts::MCTS::expansion(std::shared_ptr<Node> node) {
  if (node->action == Action::SURRENDER) return;

  if (node->action == Action::DOUBLE) return;

  for (int i = 0; i < MAX_CHILDREN; ++i) {
    auto child = std::make_shared<Node>();
    child->parent = node;
    child->action = static_cast<Action>(i);
    node->children[i] = child;
  }
}

void mcts::MCTS::backpropagation(std::shared_ptr<Node> node, int result) {
  while (node != nullptr) {
    node->visits++;
    node->wins += result;
    node = node->parent;
  }
}

void mcts::MCTS::playout(std::shared_ptr<Node> node) {
  auto cardPoolCopy = _knownCardPool;

  // shuffle the cardPool
  std::shuffle(cardPoolCopy.begin(), cardPoolCopy.end(),
               std::default_random_engine(std::random_device()()));



  auto dealerVisibleCardsCopy = _dealerVisibleCards;

  // simulate banker card

  int point = Poker::getPokerValue(node->pokers);

  switch (node->action) {
    case Action::HIT:
      node->pokers.push_back(_knownCardPool.back());
      cardPoolCopy.pop_back();
      break;
    case Action::STAND:
      break;
    case Action::DOUBLE:
      node->pokers.push_back(_knownCardPool.back());
      cardPoolCopy.pop_back();
      break;
    case Action::SURRENDER:

      backpropagation(node, -1);

      break;
    case Action::INSURANCE:

      break;
  }

  int playerScore = Poker::getPokerValue(node->pokers);

  if (playerScore > 21) {
    backpropagation(node, -1 * (node->action == Action::DOUBLE ? 2 : 1));
    return;
  }

  // simulate dealer's turn
  // because we only know one card on banker's hand
  if (dealerVisibleCardsCopy.size() == 1 && !cardPoolCopy.empty()) {
    dealerVisibleCardsCopy.push_back(cardPoolCopy.back());
    cardPoolCopy.pop_back();
  }

  int dealerScore = Poker::getPokerValue(dealerVisibleCardsCopy);

  // banker need to hit until 17
  while (dealerScore < 17 && !cardPoolCopy.empty()) {
    dealerVisibleCardsCopy.push_back(cardPoolCopy.back());
    cardPoolCopy.pop_back();
    dealerScore = Poker::getPokerValue(dealerVisibleCardsCopy);
  }

  int result = 0;

  if (playerScore > 21 && dealerScore > 21) {
    result = 0;

  } else if (playerScore > 21) {
    result = -1 * (node->action == Action::DOUBLE ? 2 : 1);

  } else if (dealerScore > 21) {
    result = 1 * (node->action == Action::DOUBLE ? 2 : 1);

  } else if (playerScore > dealerScore) {
    result = 1 * (node->action == Action::DOUBLE ? 2 : 1);

  } else if (playerScore < dealerScore) {
    result = -1 * (node->action == Action::DOUBLE ? 2 : 1);

  } else {
    result = 0;
  }
}