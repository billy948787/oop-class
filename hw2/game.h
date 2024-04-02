#ifndef GAME_H
#define GAME_H
#include <vector>

#include "player.h"
#include "poker.h"
#include "operation.h"
#include "operation_controller.h"
#include "dealer.h"
#include "manual_operation.h"
#include "ai_operation.h"

class Game {
 private:
  // singleton
  Game();
  static Game* _instance;

  int _rounds;
  int _currentRound;
  int _playerCount;
  int _leastBet;
  std::vector<Player> _players;
  std::vector<Player> _leaderboard;
  Player* _banker;

  std::vector<Poker> _cardPool;

  void _init();

  void _updateLeaderboard();
  void _printLeaderboard();

  void _initCardPool();

  void _decideTheBanker();

  void _showAllCard();

  void _askInsuranceForAllPlayers();

  void _askForDoubleOrSurrender();

  void _drawForAllPlayers();

  friend class Operation;

 public:
  static Game& getInstance();

  void start();
};

#endif