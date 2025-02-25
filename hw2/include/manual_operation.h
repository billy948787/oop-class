#ifndef MANUAL_OPERATION_H
#define MANUAL_OPERATION_H
#include "operation.h"

class ManualOperation : public Operation {
 public:
  std::map<std::string, bool> doubleOrSurrender(int);
  bool hit(std::vector<Poker>, std::vector<Poker>);
  bool insurance();
  int stake(int);
};

#endif