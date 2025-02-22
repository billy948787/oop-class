#ifndef AI_OPERATION_H
#define AI_OPERATION_H
#include "operation.h"

class AIOperation : public Operation {
 public:
  std::map<std::string, bool> doubleOrSurrender(int);
  bool hit(int);
  bool insurance();
  int stake(int);
};

#endif