#ifndef WALL_H
#define WALL_H
#include "object.h"

class Wall : public Object {
 public:
  Wall(int row, int column);
};

#endif