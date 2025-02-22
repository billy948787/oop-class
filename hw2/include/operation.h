#ifndef OPERATION_H
#define OPERATION_H
#include <map>
#include <string>

class Operation {
 public:
  virtual std::map<std::string, bool> doubleOrSurrender(int) = 0;
  virtual bool hit(int) = 0;
  virtual bool insurance() = 0;
  virtual int stake(int) = 0;
};

#endif