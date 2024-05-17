#ifndef OPERATION_H
#define OPERATION_H

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#elif defined(__APPLE__)
#include <ncurses.h>
#endif

#include <iostream>
#include <typeinfo>

#include "map.h"
#include "movement.h"

class Operation {
 private:
  Operation();
  static Operation* _instance;

 public:
  // singleton
  static Operation& getInstance();

  Movement getMovement();

  void movePlayerAndPush(Movement movement);

  
};

#endif