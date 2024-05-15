#ifndef GAME_H
#define GAME_H
#include <chrono>
#include <thread>

#include "map.h"
#include "operation.h"
class Game {
 public:
  static Game& getInstance();

  void start();

  void clearAndPrint();

  void checkGameOver();

 private:
  Game();
  static Game* _instance;
};

#endif