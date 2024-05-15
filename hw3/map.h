#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "box.h"
#include "destination.h"
#include "object.h"
#include "player.h"
#include "road.h"
#include "wall.h"

class Map {
 public:
  void print();
  // singleton
  static Map& getInstance();

  bool isGameOver();

  void updateMap();

 private:
  // singleton
  static Map* _instance;
  Map();

  int _destinations;  // number of destinations

  std::vector<std::string> originMap;
  std::vector<std::vector<Object> > transMap;
};

#endif