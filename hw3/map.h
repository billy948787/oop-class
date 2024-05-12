#ifndef MAP_H
#define MAP_H
#include <vector>
#include <string>
#include <fstream>
#include "object.h"

class Map {
 public:
  Map();
  void print();

 private:
  std::vector<std::string> originMap;
  std::vector<Object> transMap;
};

#endif