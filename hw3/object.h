#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

#include "movement.h"
#include "type.h"

class Object {
 public:
  int column, row;
  bool movable;
  char symbol;

  Object(int row, int column, bool movable, char symbol)
      : column(column), row(row), movable(movable), symbol(symbol) {}

  virtual void showPosition() {
    std::cout << "Row: " << row << " Column: " << column << std::endl;
  }

  virtual void move(Movement movement) {
    if (movable) {
      switch (movement) {
        case Movement::up:
          this->row--;
          break;
        case Movement::down:
          this->row++;
          break;
        case Movement::left:
          this->column--;
          break;
        case Movement::right:
          this->column++;
          break;
        case Movement::quit:
          break;
        case Movement::reset:
          break;
        default:
          break;
      }
    }
  }

  virtual char getSymbol() { return symbol; }

  virtual Type getType() = 0;

  Object& operator=(const Object& object) {
    this->column = object.column;
    this->row = object.row;
    this->movable = object.movable;
    this->symbol = object.symbol;

    return *this;
  }
};

#endif