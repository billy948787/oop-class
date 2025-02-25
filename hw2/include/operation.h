#ifndef OPERATION_H
#define OPERATION_H
#include <map>
#include <string>

#include "poker.h"

class Operation {
 public:
  virtual std::map<std::string, bool> doubleOrSurrender(int) = 0;
  virtual bool hit(std::vector<Poker> cards,
                   std::vector<Poker> bankerCards) = 0;
  virtual bool insurance() = 0;
  virtual int stake(int) = 0;
};

#endif