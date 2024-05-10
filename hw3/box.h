#ifndef BOX_H
#define BOX_H
#include "movement.h"
#include "object.h"

class Box : public Object {
 public:
  Box(int x, int y);

  void push(Movement);
};

#endif