#include "ai_operation.h"

#include <chrono>
#include <thread>

#include "game.h"
const int sleepTime = 2000;

bool AIOperation::hit(int point) {
  std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
  if (point < 17) {
    return true;
  } else {
    return false;
  }
}

std::map<std::string, bool> AIOperation::doubleOrSurrender(int point) {
  std::map<std::string, bool> result;

  if (point == 10) {
    result["double"] = false;
    result["surrender"] = false;
  } else if (point == 11) {
    result["double"] = true;
    result["surrender"] = false;
  } else if (point == 12) {
    result["double"] = false;
    result["surrender"] = true;
  } else if (point == 13) {
    result["double"] = false;
    result["surrender"] = true;
  } else if (point == 14) {
    result["double"] = false;
    result["surrender"] = true;
  } else if (point == 15) {
    result["double"] = false;
    result["surrender"] = true;
  } else if (point == 16) {
    result["double"] = false;
    result["surrender"] = true;
  } else {
    result["double"] = false;
    result["surrender"] = false;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

  return result;
}

bool AIOperation::insurance() {
  std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
  return true;
}

int AIOperation::stake(int money) {
  std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
  Game game = Game::getInstance();
  int leastBet = game.getLeasetBet();
  
  return leastBet;
}
