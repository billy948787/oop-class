#ifndef PLAYER_H
#define PLAYER_H

#include "movement.h"
#include "object.h"

class Player : public Object {
 public:
  Player(int x, int y);

  void move(Movement);
};

#endif