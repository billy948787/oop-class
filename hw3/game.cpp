#include "game.h"

Game* Game::_instance = nullptr;

Game::Game() {}

Game& Game::getInstance() {
  if (_instance == nullptr) {
    _instance = new Game();
  }

  return *_instance;
}

void Game::start() {
  // get the map instance
  Map& map = Map::getInstance();
  Operation operation = Operation::getInstance();

  // loop until the game is over
  while (true) {
    // clear the terminal and print the map
    clearAndPrint();
    // get user input
    Movement movement = operation.getMovement();
    // move the player
  }
}

void Game::clearAndPrint() {
  Map& map = Map::getInstance();
#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#elif defined(__APPLE__)
  system("clear");
#endif
  map.print();
}

void Game::checkGameOver() {
  Map& map = Map::getInstance();

  if (map.isGameOver()) {
    std::cout << "Game Over!" << std::endl;
    exit(0);
  }
}
