#ifndef ROAD_H
#define ROAD_H

#include "movement.h"
#include "object.h"

class Road : public Object {
 public:
  Road(int row, int column);

  Type getType() override;
};

#endif