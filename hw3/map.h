#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>

#include "box.h"
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

  Object* player;

  std::vector<std::vector<Object*> > transMap;
  std::vector<std::vector<int> > destinations;

  bool isDestination(int, int);

  bool isWall(int, int);
  bool isBox(int, int);
  bool isRoad(int, int);

  void swap(Type, Type, int, int, int, int);

  void resetMap();

  bool isDeadEnd();

  bool detectCollisionAndMove(Object*, Movement, int, int);

 private:
  // singleton
  static Map* _instance;
  Map();

  int _destinations;  // number of destinations

  std::vector<std::string> originMap;
};

#endif