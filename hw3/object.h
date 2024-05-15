#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

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

  virtual char getSymbol() { return symbol; }
};

#endif