#include "game.h"

#include <algorithm>
#include <iostream>

// make it singleton
Game* Game::_instance = nullptr;
Game& Game::getInstance() {
  if (_instance == nullptr) {
    _instance = new Game();
  }
  return *_instance;
}
// constructor
Game::Game() : _banker(nullptr) {}

// game start
void Game::start() {
  std::cout << "Game start!"
            << "\n";
  std::cout << "How many games do you want to play?"
            << "\n";
  std::cin >> _rounds;
  std::cout << "How many players?"
            << "\n";
  std::cin >> _playerCount;
  // create player
  _players.push_back(Player("Player1", *new ManualOperation()));
  for (int i = 1; i < _playerCount; i++) {
    _players.push_back(
        Player("Player" + std::to_string(i + 1), *new AIOperation()));
  }

  _currentRound = 1;

  // game start
  while (_rounds-- > 0) {
    std::cout << "Round " << _currentRound++ << " start!"
              << "\n";
    // init every round
    _init();
    //  shuffle the card
    Dealer::shuffle(_cardPool);
    // deal the card to the players include banker
    Dealer::deal(_players, _cardPool);
    Dealer::deal(_players, _cardPool);
    // fold the banker's second card
    _banker->getPokers()[1].flipTheCard();
    // show all card's to the player
    _showAllCard();
    // ask every player to draw card
    _drawForAllPlayers();

    Dealer::reduceCard(_players);
  }

  std::cout << "Game end!"
            << "\n";
}

// print the leaderboard
void Game::_printLeaderboard() {
  _updateLeaderboard();
  std::cout << _banker->getName() << "(banker)"
            << "have : " << _banker->getMoney() << "dollars!\n"
            << "(" << ((_banker->getProfit() > 0) ? "+" : "")
            << _banker->getProfit() << ")\n";
  for (auto player : _players) {
    if (player._isBanker) continue;

    std::cout << player.getName() << "have : " << player.getMoney()
              << "dollars!\n"
              << "(" << ((player.getProfit() > 0) ? "+" : "")
              << player.getProfit() << ")\n";
  }
  int i = 1;
  for (auto player : _leaderboard) {
    std::cout << i++ << ":\n"
              << player.getName() << " Money: " << player.getMoney() << "\n";
  }
}
// get the player list and sort it with the money then update the leaderboard
void Game::_updateLeaderboard() {
  _leaderboard = _players;
  // sort players by money
  std::sort(_leaderboard.begin(), _leaderboard.end(),
            [](Player a, Player b) { return a.getMoney() > b.getMoney(); });
}

void Game::_initCardPool() {
  // clear the pool first
  if (!_cardPool.empty()) _cardPool.clear();
  // add the cards to the pool
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j <= 13; j++) {
      Poker poker;
      Suit suit;
      switch (i) {
        case 0:
          suit = spade;
          if (j == 1) {
            poker.setNumber("A");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 11) {
            poker.setNumber("J");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 12) {
            poker.setNumber("Q");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 13) {
            poker.setNumber("K");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }

          poker.setNumber(std::to_string(j));
          poker.setSuit(suit);
          _cardPool.push_back(poker);
          break;

        case 1:
          suit = heart;
          if (j == 1) {
            poker.setNumber("A");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 11) {
            poker.setNumber("J");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 12) {
            poker.setNumber("Q");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 13) {
            poker.setNumber("K");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }

          poker.setNumber(std::to_string(j));
          poker.setSuit(suit);
          _cardPool.push_back(poker);
          break;

        case 2:
          suit = diamond;
          if (j == 1) {
            poker.setNumber("A");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 11) {
            poker.setNumber("J");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 12) {
            poker.setNumber("Q");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 13) {
            poker.setNumber("K");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }

          poker.setNumber(std::to_string(j));
          poker.setSuit(suit);
          _cardPool.push_back(poker);
          break;
        case 3:
          suit = club;
          if (j == 1) {
            poker.setNumber("A");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 11) {
            poker.setNumber("J");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 12) {
            poker.setNumber("Q");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }
          if (j == 13) {
            poker.setNumber("K");
            poker.setSuit(suit);
            _cardPool.push_back(poker);
            break;
          }

          poker.setNumber(std::to_string(j));
          poker.setSuit(suit);
          _cardPool.push_back(poker);
          break;
      }
    }
  }
}

void Game::_decideTheBanker() {
  int highest = -1e9;
  int highestPlayers = 1;

  // clear the banker first
  if (_banker != nullptr) {
    _banker->switchBanker();
    _banker = nullptr;
  }

  // the first round
  if (_currentRound == 1) {
    srand(time(NULL));
    _banker = &_players[rand() % _players.size()];
    _banker->switchBanker();
    return;
  }

  for (auto& player : _players) {
    if (player.getProfit() > highest) {
      highestPlayers = 1;
      highest = player.getProfit();
      _banker = &player;
    }
    if (player.getProfit() == highest) {
      highestPlayers++;
    }
  }
  // the highest(profit from last round) player > 1
  if (highestPlayers > 1) {
    int lowestMoney = 1e9;
    for (auto& player : _players) {
      if (player.getProfit() == highest) {
        if (player.getMoney() < lowestMoney) {
          lowestMoney = player.getMoney();
          _banker = &player;
        }
      }
    }
  }

  _banker->switchBanker();
}

void Game::_init() {
  _initCardPool();
  _decideTheBanker();
}

void Game::_showAllCard() {
  std::cout << _banker->getName() << "(banker) "
            << "points : " << _banker->getPoint() << "\n";

  Poker::printPokers(_banker->getPokers());

  for (auto player : _players) {
    if (player._isBanker) continue;
    std::cout << player.getName() << " points : " << player.getPoint() << "\n";
    Poker::printPokers(player.getPokers());
  }
}

void Game::_drawForAllPlayers() {
  for (auto& player : _players) {
    if(_banker->getPokers()[0].getNumber() == "A"){
      bool takeInsurance = player._operationController.insurance();
      if(takeInsurance){
        player._hasInsurance = true;
        player.reduceMoney(player._bet / 2);
        player.
      }
    }
  }
}