#ifndef PLAYER_H
#define PLAYER_H

#include "movement.h"
#include "object.h"

class Player : public Object {
 public:
  Player(int row, int column);

  Type getType() override;
};

#endif