#include "game.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#define DEFAULT "\033[0;1m"
#define REDBACKGROUND "\033[41;1m"
#define GREENBACKGROUND "\033[42;1m"

const int sleepTime = 1000;

// make it singleton
Game *Game::_instance = nullptr;
Game &Game::getInstance() {
  if (_instance == nullptr) {
    _instance = new Game();
  }
  return *_instance;
}
// constructor
Game::Game() : _banker(nullptr), _leastBet(1000), _isRunning(true) {}

// game start
void Game::start() {
  std::cout << "Game start!"
            << "\n";
  // input the player count
  _inputPlayerCount();
  // input the round count
  _inputRoundCount();

  std::cout << "What is your name?"
            << "\n";
  std::string name;
  std::cin >> name;
  // create player
  _players.push_back(Player(name, *new ManualOperation()));

  for (int i = 1; i < _playerCount; i++) {
    _players.push_back(
        Player("Player" + std::to_string(i + 1) + "(AI)", *new AIOperation()));
  }

  _currentRound = 0;

  // game start
  while (_rounds-- > 0 && _isRunning) {
    std::cout << "Round " << ++_currentRound << " start!"
              << "\n";
    // init every round
    _init();
    // tell the player the banker
    std::cout << REDBACKGROUND << "*** The banker is " << _banker->getName()
              << " ***" << DEFAULT << "\n";
    // ask every player to stake
    _askForStake();
    //  shuffle the card
    Dealer::shuffle(_cardPool);
    std::cout << "Shuffling the card"
              << "\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    // deal the card to the players include banker
    Dealer::deal(_players, _cardPool);
    Dealer::deal(_players, _cardPool);
    // fold the banker's second card
    _banker->getPokers()[1].flipTheCard();
    // show all card's to the player
    _showAllCard();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // ask every player to double surrender or do nothing
    _askForDoubleOrSurrender();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // ask every player to take insurance or not
    _askInsuranceForAllPlayers();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // ask every player to draw card
    _drawForAllPlayers();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // ask the banker to draw card
    _drawForBanker();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // settle the game
    _settle();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

    // reduce the card
    Dealer::reduceCard(_players);
    // print the leaderboard
    _printLeaderboard();
    // std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    // kick out the player who can't afford the least bet or has no money
    _kickOut();
  }

  std::cout << "Game end!"
            << "\n";

  _printFinalLeaderboard();
}

void Game::_inputPlayerCount() {
  std::string input;
  std::cout << "How many players?(2-4)"
            << "\n";

  while (true) {
    std::cin >> input;
    bool isNumber = true;
    for (auto element : input) {
      if (element > 57 || element < 48) {
        std::cout << "Please enter valid number!\n";
        isNumber = false;
        break;
      }
    }

    if (isNumber) {
      if (std::stoi(input) < 2 || std::stoi(input) > 4) {
        std::cout << "Please enter valid number!\n";
        continue;
      } else {
        _playerCount = std::stoi(input);

        break;
      }
    }
  }
}

void Game::_inputRoundCount() {
  std::string input;
  std::cout << "How many games do you want to play?"
            << "\n";

  while (true) {
    std::cin >> input;
    bool isNumber = true;
    for (auto element : input) {
      if (element > 57 || element < 48) {
        std::cout << "Please enter valid number!\n";
        isNumber = false;
        break;
      }
    }

    if (isNumber) break;
  }
  _rounds = std::stoi(input);
}

// print the leaderboard
void Game::_printLeaderboard() {
  _updateLeaderboard();
  // change the color
  std::cout << GREENBACKGROUND << "The result is:" << DEFAULT << "\n";

  std::cout << _banker->getName() << "(banker)"
            << "have : " << _banker->getMoney() << "dollars!\n"
            << ((_banker->getProfit() > 0) ? GREENBACKGROUND : REDBACKGROUND)
            << "(" << ((_banker->getProfit() > 0) ? "+" : "")
            << _banker->getProfit() << ")" << DEFAULT << "\n";
  for (auto player : _players) {
    if (player._isBanker) continue;
    if (player._isOut) continue;

    std::cout << player.getName() << "have : " << player.getMoney()
              << "dollars!\n"
              << ((player.getProfit() > 0) ? GREENBACKGROUND : REDBACKGROUND)
              << "(" << ((player.getProfit() > 0) ? "+" : "")
              << player.getProfit() << ")" << DEFAULT << "\n";
  }

  std::cout << GREENBACKGROUND << "The leaderboard is:" << DEFAULT << "\n";
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

void Game::_printFinalLeaderboard() {
  _updateLeaderboard();
  std::cout << GREENBACKGROUND << "The final leaderboard is:" << DEFAULT
            << "\n";
  int i = 1;
  for (auto player : _leaderboard) {
    std::cout << i++ << ":\n"
              << player.getName() << (player._isOut ? "(out)" : "")
              << " Money: " << player.getMoney()
              << ((player.getTotalProfit() > 0) ? GREENBACKGROUND
                                                : REDBACKGROUND)
              << "("
              << (player.getTotalProfit() > 0
                      ? "+" + std::to_string(player.getTotalProfit())
                      : std::to_string(player.getTotalProfit()))
              << ")" << DEFAULT << "\n";
  }
}

void Game::_printAction(std::string action, bool isAI) {
  isAI ? std::cout << " has chosen to " << action << "\n" : std::cout << "";
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

void Game::_askForStake() {
  for (auto &player : _players) {
    if (player._isBanker) continue;
    if (player._isOut) continue;

    std::cout << player.getName() << " : ";

    int stake = player._operationController.stake(player.getMoney());

    _printAction("stake " + std::to_string(stake), player._isAI);

    player.callBet(stake);
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

  for (auto &player : _players) {
    if (player._isOut) continue;
    if (player.getProfit() > highest) {
      highestPlayers = 1;
      highest = player.getProfit();
      _banker = &player;
      continue;
    }
    if (player.getProfit() == highest) {
      highestPlayers++;
    }
  }
  // the highest(profit from last round) player > 1
  if (highestPlayers > 1) {
    int lowestMoney = 1e9;
    for (auto &player : _players) {
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
  // clear the player's state
  for (auto &player : _players) {
    player.clearState();
  }
}

void Game::_showAllCard() {
  std::cout << _banker->getName() << "(banker) "
            << "points : " << _banker->getPoint() << "\n";

  Poker::printPokers(_banker->getPokers());

  for (auto &player : _players) {
    if (player._isBanker) continue;
    if (player._isOut) continue;
    std::cout << player.getName() << " points : " << player.getPoint() << "\n";
    Poker::printPokers(player.getPokers());
  }
}

void Game::_askInsuranceForAllPlayers() {
  if (_banker->getPokers()[0].getNumber() != "A") return;
  for (auto &player : _players) {
    if (player._isBanker) continue;
    if (player._surrendered) continue;
    if (player._isOut) continue;

    std::cout << player.getName() << " : ";

    if (_banker->getPokers()[0].getNumber() == "A") {
      bool takeInsurance = player._operationController.insurance();
      if (takeInsurance) {
        player._hasInsurance = true;

        _printAction("take the insurance", player._isAI);
      } else {
        _printAction("not take the insurance", player._isAI);
      }
    }
  }
}

void Game::_askForDoubleOrSurrender() {
  for (auto &player : _players) {
    if (player._isBanker) continue;
    if (player._isOut) continue;

    std::cout << player.getName() << " : ";

    std::map<std::string, bool> result =
        player._operationController.doubleOrSurrender(player.getPoint());

    if (result["double"]) {
      _printAction("double down", player._isAI);

      player._doubled = true;
    } else if (result["surrender"]) {
      player._surrendered = true;

      _printAction("surrender", player._isAI);
    } else {
      _printAction("do nothing", player._isAI);
    }
  }
}

void Game::_drawForAllPlayers() {
  for (auto &player : _players) {
    if (player._isBanker) continue;
    if (player._isOut) continue;

    while (true) {
      if (player._surrendered) break;

      if (player._doubled) {
        player.doubleDown();

        Dealer::deal(player, _cardPool, false);

        std::cout << player.getName() << " :  has got these cards now:\n\n";

        std::cout << "Point : " << player.getPoint() << "\n";
        Poker::printPokers(player.getPokers());

        if (player.getPoint() == 21) {
          std::cout << player.getName() << " :  has reached 21 points\n";
          break;
        }

        if (player.getPoint() > 21) {
          std::cout << player.getName() << " :  has busted.\n";
          break;
        }

        break;
      }

      std::cout << player.getName() << " : ";

      bool toHit = player._operationController.hit(player.getPoint());

      if (toHit) {
        Dealer::deal(player, _cardPool, false);

        std::cout << " has got these cards now:\n\n";
        std::cout << "Point : " << player.getPoint() << "\n";
        Poker::printPokers(player.getPokers());

        if (player.getPoint() == 21) {
          std::cout << player.getName() << " :  has reached 21 points\n";
          break;
        }

        if (player.getPoint() > 21) {
          std::cout << player.getName() << " :  has busted.\n";
          break;
        }
      } else {
        _printAction("not hit", player._isAI);
        break;
      }
    }
  }
}

void Game::_drawForBanker() {
  // flip the card back
  _banker->getPokers()[1].flipTheCard();

  std::cout << _banker->getName() << "(banker)"
            << " :  has got these cards now:\n\n";
  std::cout << "Point : " << _banker->getPoint() << "\n";
  Poker::printPokers(_banker->getPokers());

  bool toHit = true;

  while (toHit) {
    if (_banker->getPoint() > 21) {
      std::cout << _banker->getName() << "(banker)"
                << " :  has busted.\n";

      return;
    }
    toHit = _banker->_operationController.hit(_banker->getPoint());

    if (toHit) {
      Dealer::deal(*_banker, _cardPool, false);
      std::cout << _banker->getName() << "(banker)"
                << " :  has got these cards now:\n\n";
      std::cout << "Point : " << _banker->getPoint() << "\n";
      Poker::printPokers(_banker->getPokers());
    }
  }
}

void Game::_settle() {
  for (auto &player : _players) {
    int point = player.getPoint();

    if (player._isBanker) continue;
    if (player._isOut) continue;

    if (player._hasInsurance) {
      if (_banker->getPokers().size() == 2 && _banker->getPoint() == 21) {
        _banker->reduceMoney(player.getBet());
        _banker->_gainedFromLastRound -= player.getBet();
        player.getInsurance();
      } else {
        _banker->addMoney(player.getBet() / 2);
        _banker->_gainedFromLastRound += player.getBet() / 2;
        player.lossInsurance();
      }
    }
    if (player._surrendered) {
      _banker->_gainedFromLastRound += player.getBet() / 2;
      _banker->addMoney(player.getBet() / 2);
      player.surrender();
      continue;
    }

    // check if the player has five card charlie
    if (point <= 21 && player.getPokers().size() == 5) {
      _banker->reduceMoney(player.getBet() * 2);
      _banker->_gainedFromLastRound -= player.getBet() * 2;
      player.winBet("five card charlie");
      continue;
    }
    // check if the player has shun
    if (point == 21 && player.getPokers().size() == 3) {
      std::map<int, bool> numberMap;
      for (auto poker : player.getPokers()) {
        if (poker.getNumber() == "6") {
          numberMap[6] = true;
        }
        if (poker.getNumber() == "7") {
          numberMap[7] = true;
        }
        if (poker.getNumber() == "8") {
          numberMap[8] = true;
        }
      }
      if (numberMap[6] && numberMap[7] && numberMap[8]) {
        _banker->reduceMoney(player.getBet() * 2);
        _banker->_gainedFromLastRound -= player.getBet() * 2;
        player.winBet("shun");
        continue;
      }
    }

    // not the special case
    if (_banker->getPoint() > 21) {
      if (player.getPoint() <= 21) {
        _banker->reduceMoney(player.getBet());
        _banker->_gainedFromLastRound -= player.getBet();
        player.winBet();
      } else {
        player.winBet("takeBetBack");
      }
      continue;
    }

    if (_banker->getPoint() <= 21) {
      // check if the player is busted
      if (player.getPoint() > 21) {
        _banker->addMoney(player.getBet());
        _banker->_gainedFromLastRound += player.getBet();
        player.loseBet();
        continue;
      }

      if (player.getPoint() > _banker->getPoint()) {
        _banker->reduceMoney(player.getBet());
        _banker->_gainedFromLastRound -= player.getBet();
        player.winBet();
      } else {
        _banker->addMoney(player.getBet());
        _banker->_gainedFromLastRound += player.getBet();
        player.loseBet();
      }
    }
  }
}
int Game::getLeasetBet() { return _leastBet; }

void Game::_kickOut() {
  for (int i = 0; i < _players.size(); i++) {
    // check if the player is out of the game or not
    if (_players[i]._isOut) continue;
    if (_players[i].getMoney() < _leastBet) {
      std::cout << _players[i].getName()
                << " has been kicked out!(can't afford the least bet)\n";
      _players[i].out();
    } else if (_players[i].getMoney() == 0) {
      std::cout << _players[i].getName() << " has been kicked out!(no money)\n";
      _players[i].out();
    }
  }

  int outCount = 0;

  for (auto player : _players) {
    if (player._isOut) outCount++;
  }

  if (outCount == _players.size() - 1) {
    _isRunning = false;
  }
}