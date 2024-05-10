#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>

class Object {
 protected:
  int x, y;
  bool movable;

  Object(int x, int y, bool movable) : x(x), y(y), movable(movable) {}

  virtual void showPosition() {
    std::cout << "X: " << x << " Y: " << y << std::endl;
  }
};

#endif