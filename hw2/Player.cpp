#include "player.h"

Player::Player(std::string name, Operation& operation)
    : _money(10000),
      _isBanker(false),
      _doubled(false),
      _surrendered(false),
      _hasInsurance(false),
      _operationController(operation),
      _bet(0),
      _isOut(false),
      _name(name) {}

void Player::switchBanker() { _isBanker = !_isBanker; }

int Player::getMoney() { return _money; }

void Player::addMoney(int money) {
  this->_money += money;
  this->_gainedFromLastRound = money;
}

void Player::doubleDown() {
  _doubled = true;
  callBet(_bet);
}

void Player::reduceMoney(int money) {
  this->_money -= money;
  this->_gainedFromLastRound = -money;
}

void Player::clearState() {
  _isBanker = false;
  _surrendered = false;
  _hasInsurance = false;
  clearBet();
  _doubled = false;
}

void Player::out() { this->_isOut = true; }

std::string Player::getName() { return _name; }

void Player::addPoker(Poker poker) { _pokers.push_back(poker); }

void Player::clearPoker() { _pokers.clear(); }

int Player::getProfit() { return _gainedFromLastRound; }

void Player::callBet(int bet) {
  this->_bet += bet;
  reduceMoney(bet);
}

void Player::clearBet() { _bet = 0; }

void Player::winBet() {
  addMoney(_bet * 2);
  _gainedFromLastRound = _bet;
  clearBet();
}

void Player::loseBet() {
  _gainedFromLastRound = -_bet;
  clearBet();
}

void Player::surrender() {
  _gainedFromLastRound = -(_bet / 2);
  _surrendered = true;
  addMoney(_bet / 2);
  clearBet();
}

std::vector<Poker>& Player::getPokers() { return _pokers; }

int Player::getPoint() {
  int point = 0;
  int count = 0;
  for (auto poker : _pokers) {
    if (!poker._isFaceUp) continue;
    if (poker.getNumber() == "A") {
      count++;
      continue;
    }
    if (poker.getNumber() == "J" || poker.getNumber() == "Q" ||
        poker.getNumber() == "K") {
      point += 10;
    } else {
      point += std::stoi(poker.getNumber());
    }
  }

  while (count-- > 0) {
    if (point + 11 > 21) {
      point += 1;
    } else {
      point += 11;
    }
  }

  return point;
}

void Player::changeOperation(Operation& operation) {
  _operationController.changeOperation(operation);
}