#include <iostream>

#include "game.h"

int main() {
  Game game = Game::getInstance();

  game.start();
}