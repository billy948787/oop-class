#ifndef ROAD_H
#define ROAD_H

#include "movement.h"
#include "object.h"

class Road : public Object {
 public:
  bool hasObjectOn = false;
  Road(int row, int column);

  void move(Movement);
};

#endif