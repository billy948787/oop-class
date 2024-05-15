#ifndef OPERATION_H
#define OPERATION_H

#include <ncurses.h>

#include <iostream>

#include "movement.h"

class Operation {
 private:
  Operation();
  static Operation* _instance;

 public:
  // singleton
  static Operation& getInstance();

  Movement getMovement();
};

#endif