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

  // print the map
  clearAndPrint();
  // sleep for 0.5 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  // loop until the game is over
  while (running) {
    // get the movement from the player
    checkOperation();
    // check if the game is over
    checkGameOver();
    // clear the screen and print the map
    clearAndPrint();
  }

  std::cout << "Game Over!" << std::endl;
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
    running = false;
  } else if (map.isDeadEnd()) {
    clearAndPrint();
    std::cout << "Dead End!" << std::endl;
    std::cout << "Press 'r' to reset the map" << std::endl;
    std::cout << "Press 'q' to quit" << std::endl;

    while (true) {
      Operation operation = Operation::getInstance();
      Movement movement = operation.getMovement();
      if (movement == Movement::reset) {
        map.resetMap();
        break;
      } else if (movement == Movement::quit) {
        running = false;
        break;
      }
    }
  }
}

void Game::checkOperation() {
  Operation operation = Operation::getInstance();
  Movement movement = operation.getMovement();
  switch (movement) {
    case Movement::up:
      operation.movePlayerAndPush(Movement::up);
      break;
    case Movement::down:
      operation.movePlayerAndPush(Movement::down);
      break;
    case Movement::left:
      operation.movePlayerAndPush(Movement::left);
      break;
    case Movement::right:
      operation.movePlayerAndPush(Movement::right);
      break;
    case Movement::reset:
      Map::getInstance().resetMap();
      break;
    case Movement::quit:
      running = false;
      break;
    default:
      break;
  }
}
