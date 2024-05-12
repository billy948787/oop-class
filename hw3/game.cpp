#include "game.h"

Game* Game::_instance = nullptr;

Game::Game() {}

Game& Game::getInstance() {
  if (_instance == nullptr) {
    _instance = new Game();
  }

  return *_instance;
}

void Game::start() {}