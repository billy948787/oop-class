#ifndef BOX_H
#define BOX_H
#include "movement.h"
#include "object.h"

class Box : public Object {
 public:
  Box(int row, int column);

  void push(Movement);
};

#endif