#include "player.h"

Player::Player(int row, int column) : Object(row, column, true, '0') {}

void Player::move(Movement movement) {
  switch (movement) {
    case up:
      this->row -= 1;
      break;

    case down:
      this->row += 1;
      break;

    case right:
      this->column += 1;
      break;

    case left:
      this->column -= 1;
      break;
  }
}