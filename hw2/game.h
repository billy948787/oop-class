#ifndef GAME_H
#define GAME_H
#include <vector>

#include "ai_operation.h"
#include "dealer.h"
#include "manual_operation.h"
#include "operation.h"
#include "operation_controller.h"
#include "player.h"
#include "poker.h"

class Game {
 private:
  // singleton
  Game();
  static Game* _instance;

  bool _isRunning;

  int _rounds;
  int _currentRound;
  int _playerCount;
  int _leastBet;
  std::vector<Player> _players;
  std::vector<Player> _leaderboard;
  Player* _banker;

  std::vector<Poker> _cardPool;

  void _inputPlayerCount();
  void _inputRoundCount();

  void _init();

  void _updateLeaderboard();
  void _printLeaderboard();
  void _printFinalLeaderboard();
  void _printAction(std::string, bool);

  void _initCardPool();

  void _decideTheBanker();

  void _showAllCard();

  void _askForStake();

  void _askInsuranceForAllPlayers();

  void _askForDoubleOrSurrender();

  void _drawForAllPlayers();

  void _drawForBanker();

  void _settle();

  void _kickOut();

  friend class Operation;

 public:
  static Game& getInstance();

  int getLeasetBet();

  void start();
};

#endif