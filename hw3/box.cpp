#include "box.h"

Box::Box(int x, int y) : Object(x, y, true) {}

void Box::push(Movement movement) {
  switch (movement) {
    case up:
      this->y -= 1;
      break;

    case down:
      this->y += 1;
      break;

    case right:
      this->x += 1;
      break;

    case left:
      this->x -= 1;
      break;
  }
}