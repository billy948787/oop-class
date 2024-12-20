#ifndef OPERATION_CONTROLLER_H
#define OPERATION_CONTROLLER_H
#include "operation.h"

class OperationController {
 public:
  OperationController(Operation&);

  std::map<std::string, bool> doubleOrSurrender(int);
  bool hit(int);
  bool insurance();
  int stake(int);

  void changeOperation(Operation& operation);

 private:
  Operation* operation;
};

#endif