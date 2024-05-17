#include "map.h"

void Map::swap(Type type1, Type type2, int row, int column, int newRow,
               int newColumn) {
  switch (type1) {
    case Type::playerType: {
      Player* player = new Player(newRow, newColumn);
      transMap[newRow][newColumn] = player;
      break;
    }
    case Type::boxType: {
      Box* box = new Box(newRow, newColumn);
      transMap[newRow][newColumn] = box;
      break;
    }
    case Type::roadType: {
      Road* road = new Road(newRow, newColumn);
      transMap[newRow][newColumn] = road;
      break;
    }
    case Type::wallType: {
      Wall* wall = new Wall(newRow, newColumn);
      transMap[newRow][newColumn] = wall;
      break;
    }
    case Type::defaultType:
      break;
  }

  switch (type2) {
    case Type::playerType: {
      Player* player = new Player(row, column);
      transMap[row][column] = player;
      break;
    }
    case Type::boxType: {
      Box* box = new Box(row, column);
      transMap[row][column] = box;
      break;
    }
    case Type::roadType: {
      Road* road = new Road(row, column);
      transMap[row][column] = road;
      break;
    }
    case Type::wallType: {
      Wall* wall = new Wall(row, column);
      transMap[row][column] = wall;
      break;
    }
    case Type::defaultType:
      break;
  }
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
      if (isDestination(i, j) && transMap[i][j]->getSymbol() == '1') {
        std::cout << "1";
      } else if (isDestination(i, j) && transMap[i][j]->getSymbol() == '0') {
        std::cout << "0";
      } else if (isDestination(i, j)) {
        std::cout << "2";
      } else {
        std::cout << transMap[i][j]->getSymbol();
      }
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
    std::vector<Object*> temp;
    for (int j = 0; j < originMap[i].size(); j++) {
      switch (originMap[i][j]) {
        // wall
        case '/': {
          Wall* wall = new Wall(i, j);
          temp.push_back(wall);
          break;
        }
        // road
        case '-': {
          Road* road = new Road(i, j);
          temp.push_back(road);
          break;
        }
        // player
        case '0': {
          Player* player = new Player(i, j);
          this->player = player;
          temp.push_back(player);
          break;
        }
        // box:
        case '1': {
          Box* box = new Box(i, j);
          temp.push_back(box);
          break;
        }
        // destination
        case '2': {
          Road* road = new Road(i, j);
          this->_destinations++;
          temp.push_back(road);
          std::vector<int> dest;
          dest.push_back(i);
          dest.push_back(j);
          destinations.push_back(dest);
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
      int newRow = transMap[i][j]->row;
      int newCol = transMap[i][j]->column;
      // check if the object is a box
      if (newRow != i || newCol != j) {
        swap(transMap[i][j]->getType(), transMap[newRow][newCol]->getType(), i,
             j, newRow, newCol);
      }
    }
  }
}
bool Map::isGameOver() {
  int count = 0;
  for (int i = 0; i < transMap.size(); i++) {
    for (int j = 0; j < transMap[i].size(); j++) {
      if (transMap[i][j]->getType() == Type::boxType && isDestination(i, j)) {
        count++;
      }
    }
  }
  if (count == _destinations) {
    return true;
  } else {
    return false;
  }
}

bool Map::isDeadEnd() {
  for (int i = 0; i < transMap.size(); i++) {
    for (int j = 0; j < transMap[i].size(); j++) {
      if (transMap[i][j]->getType() == Type::boxType) {
        if (isDestination(i, j)) continue;
        if (isWall(i - 1, j) && isWall(i, j - 1)) {
          return true;
        } else if (isWall(i - 1, j) && isWall(i, j + 1)) {
          return true;
        } else if (isWall(i + 1, j) && isWall(i, j - 1)) {
          return true;
        } else if (isWall(i + 1, j) && isWall(i, j + 1)) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Map::isDestination(int row, int column) {
  for (int i = 0; i < destinations.size(); i++) {
    if (destinations[i][0] == row && destinations[i][1] == column) {
      return true;
    }
  }

  return false;
}

bool Map::isWall(int row, int column) {
  if (row < 0 || column < 0 || row >= transMap.size() ||
      column >= transMap[row].size()) {
    return true;
  } else if (transMap[row][column]->getType() == Type::wallType) {
    return true;
  } else {
    return false;
  }
}

bool Map::isBox(int row, int column) {
  if (transMap[row][column]->getType() == Type::boxType) {
    return true;
  } else {
    return false;
  }
}

bool Map::isRoad(int row, int column) {
  if (transMap[row][column]->getType() == Type::roadType) {
    return true;
  } else {
    return false;
  }
}

bool Map::detectCollisionAndMove(Object* object, Movement movement, int row,
                                 int column) {
  switch (movement) {
    case Movement::up:
      if (row - 1 < 0) return false;
      if (isWall(row - 1, column)) return false;
      if (object->getType() == Type::boxType && isBox(row - 1, column))
        return false;
      if (isRoad(row - 1, column)) {
        object->move(movement);
        transMap[row - 1][column]->move(Movement::down);
        updateMap();
        return true;
      }

      if (isBox(row - 1, column) && object->getType() == Type::playerType) {
        if (detectCollisionAndMove(transMap[row - 1][column], movement, row - 1,
                                   column)) {
          object->move(movement);
          transMap[row - 1][column]->move(Movement::down);
          updateMap();
          return true;
        }
      }

      break;

    case Movement::left:
      if (column - 1 < 0) return false;
      if (isWall(row, column - 1)) return false;
      if (object->getType() == Type::boxType && isBox(row, column - 1))
        return false;
      if (isRoad(row, column - 1)) {
        object->move(movement);
        transMap[row][column - 1]->move(Movement::right);
        updateMap();
        return true;
      }

      if (isBox(row, column - 1) && object->getType() == Type::playerType) {
        if (detectCollisionAndMove(transMap[row][column - 1], movement, row,
                                   column - 1)) {
          object->move(movement);
          transMap[row][column - 1]->move(Movement::right);
          updateMap();
          return true;
        }
      }

      break;

    case Movement::down:
      if (row + 1 >= transMap.size()) return false;
      if (isWall(row + 1, column)) return false;
      if (object->getType() == Type::boxType && isBox(row + 1, column))
        return false;
      if (isRoad(row + 1, column)) {
        object->move(movement);
        transMap[row + 1][column]->move(Movement::up);
        updateMap();
        return true;
      }

      if (isBox(row + 1, column) && object->getType() == Type::playerType) {
        if (detectCollisionAndMove(transMap[row + 1][column], movement, row + 1,
                                   column)) {
          object->move(movement);
          transMap[row + 1][column]->move(Movement::up);
          updateMap();
          return true;
        }
      }

      break;

    case Movement::right:
      if (column + 1 >= transMap[row].size()) return false;
      if (isWall(row, column + 1)) return false;
      if (object->getType() == Type::boxType && isBox(row, column + 1))
        return false;
      if (isRoad(row, column + 1)) {
        object->move(movement);
        transMap[row][column + 1]->move(Movement::left);
        updateMap();
        return true;
      }

      if (isBox(row, column + 1) && object->getType() == Type::playerType) {
        if (detectCollisionAndMove(transMap[row][column + 1], movement, row,
                                   column + 1)) {
          object->move(movement);
          transMap[row][column + 1]->move(Movement::left);
          updateMap();
          return true;
        }
      }

      break;

    default:
      return false;
  }

  return false;
}

void Map::resetMap() {
  transMap.clear();
  for (int i = 0; i < originMap.size(); i++) {
    std::vector<Object*> temp;
    for (int j = 0; j < originMap[i].size(); j++) {
      switch (originMap[i][j]) {
        // wall
        case '/': {
          Wall* wall = new Wall(i, j);
          temp.push_back(wall);
          break;
        }
        // road
        case '-': {
          Road* road = new Road(i, j);
          temp.push_back(road);
          break;
        }
        // player
        case '0': {
          Player* player = new Player(i, j);
          this->player = player;
          temp.push_back(player);
          break;
        }
        // box:
        case '1': {
          Box* box = new Box(i, j);
          temp.push_back(box);
          break;
        }
        // destination
        case '2': {
          Road* road = new Road(i, j);
          this->_destinations++;
          temp.push_back(road);
          std::vector<int> dest;
          dest.push_back(i);
          dest.push_back(j);
          destinations.push_back(dest);
          break;
        }
      }
    }
    transMap.push_back(temp);
  }
}