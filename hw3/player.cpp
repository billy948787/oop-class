#include "player.h"

Player::Player(int row, int column) : Object(row, column, true, '0') {}

Type Player::getType() { return Type::playerType; }