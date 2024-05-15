#include "map.h"

void swap(Object& obj1, Object& obj2) {
  Object temp = obj1;
  obj1 = obj2;
  obj2 = temp;
}

Map* Map::_instance = nullptr;

Map& Map::getInstance() {
  if (_instance == nullptr) {
    _instance = new Map();
  }

  return *_instance;
}

void Map::print() {
  // update the map
  updateMap();
  for (int i = 0; i < transMap.size(); i++) {
    for (int j = 0; j < transMap[i].size(); j++) {
      std::cout << transMap[i][j].getSymbol();
    }
    std::cout << std::endl;
  }
}

Map::Map() : _destinations(0) {
  std::string fileName = "input.txt";
  while (true) {
    std::string input;

    std::cout << "Enter the file name (or press Enter to use "
                 "default(\"input.txt\")): ";
    std::getline(std::cin, input);

    if (input.empty()) {
      break;
    } else {
      fileName = input;
      break;
    }
  }

  std::fstream file;
  // open the file
  file.open(fileName, std::ios::in);
  // check if the file is opened
  if (!file.is_open()) {
    std::cout << "File not found!" << std::endl;
    std::cout << "Exiting..." << std::endl;
    exit(1);
  }

  int n, m;
  // catch the n and m
  file >> n >> m;

  while (!file.eof()) {
    std::string line;
    std::getline(file, line);
    originMap.push_back(line);
  }

  file.close();

  for (int i = 0; i < originMap.size(); i++) {
    std::vector<Object> temp;
    for (int j = 0; j < originMap[i].size(); j++) {
      switch (originMap[i][j]) {
        // wall
        case '/': {
          Wall Wall(i, j);
          temp.push_back(Wall);
          break;
        }
        // road
        case '-': {
          Road Road(i, j);
          temp.push_back(Road);
          break;
        }
        // player
        case '0': {
          Player Player(i, j);
          temp.push_back(Player);
          break;
        }
        // box:
        case '1': {
          Box Box(i, j);
          temp.push_back(Box);
          break;
        }
        // destination
        case '2': {
          Destination Destination(i, j);
          this->_destinations++;
          temp.push_back(Destination);
          break;
        }
      }
    }
    transMap.push_back(temp);
  }
}

void Map::updateMap() {
  for (int i = 0; i < transMap.size(); i++) {
    for (int j = 0; j < transMap[i].size(); j++) {
      int newRow = transMap[i][j].row;
      int newCol = transMap[i][j].column;
      // check if the object is a box
      if (newRow != i || newCol != j) {
        swap(transMap[i][j], transMap[newRow][newCol]);
      }
    }
  }
}
bool Map::isGameOver() {
  int count = 0;
  for (int i = 0; i < transMap.size(); i++) {
    for (int j = 0; j < transMap[i].size(); j++) {
      if (typeid(transMap[i][j]) == typeid(Destination)) {
        Destination& destination =
            reinterpret_cast<Destination&>(transMap[i][j]);

        if (destination.hasBoxOn) count++;
      }
    }
  }

  if (count == this->_destinations)
    return true;
  else
    return false;
}
