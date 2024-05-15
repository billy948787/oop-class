#include "box.h"

Box::Box(int row, int column) : Object(row, column, true, '1') {}

void Box::push(Movement movement) {
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