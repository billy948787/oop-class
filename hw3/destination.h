#ifndef DESTINATION_H
#define DESTINATION_H
#include "object.h"

class Destination : public Object {
 public:
  bool hasBoxOn;

  Destination(int row, int column );
};

#endif