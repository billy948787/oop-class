#include "operation.h"

Operation* Operation::_instance = nullptr;

Operation::Operation() {}

Operation& Operation::getInstance() {
  if (_instance == nullptr) {
    _instance = new Operation();
  }

  return *_instance;
}

Movement Operation::getMovement() {
  Movement result = Movement::down;
  int input = 0;

#if defined(_WIN32) || defined(_WIN64)
  input = _getch();
#elif defined(__APPLE__)
  initscr();
  cbreak();
  noecho();

  input = getch();

  endwin();
#endif

  switch (input) {
    case 'w':
      result = Movement::up;
      break;
    case 'a':
      result = Movement::left;
      break;
    case 's':
      result = Movement::down;
      break;
    case 'd':
      result = Movement::right;
      break;
    case 'q':
      std::cout << "Exiting game..." << std::endl;
      exit(0);
      break;
    default:
      break;
  }

  return result;
}

void Operation::movePlayerAndPush(Movement movement) {
  Map& map = Map::getInstance();
  // find player
  for (int i = 0; i < map.transMap.size(); i++) {
    for (int j = 0; j < map.transMap[i].size(); j++) {
      if (typeid(map.transMap[i][j]) == typeid(Player)) {
        Player& player = reinterpret_cast<Player&>(map.transMap[i][j]);
        switch (movement) {
          case up:
            // check if the player can move up if it is box on top of it
            // push the box
            if (i - 1 >= 0) {
              // check if the player can move up
              if (typeid(map.transMap[i - 1][j]) == typeid(Box) && i - 2 >= 0) {
                if (typeid(map.transMap[i - 2][j]) == typeid(Wall)) {
                  break;
                } else if (typeid(
                               map.transMap[i - 2][j]) ==  // check if the box
                                                           // is on destination
                           typeid(Destination)) {
                  Destination& destination =
                      reinterpret_cast<Destination&>(map.transMap[i - 2][j]);
                  Box& box = reinterpret_cast<Box&>(map.transMap[i - 1][j]);
                  Road& road = reinterpret_cast<Road&>(map.transMap[i - 2][j]);
                  destination.hasBoxOn = true;
                  box.push(Movement::up);
                  player.move(movement);



                } else {  // if the box is not on destination
                  Box& box = reinterpret_cast<Box&>(map.transMap[i - 1][j]);
                  Road& road = reinterpret_cast<Road&>(map.transMap[i - 2][j]);
                  player.move(movement);
                  box.push(Movement::up);
                  road.move(Movement::down);
                  road.move(Movement::down);
                }
              } else {
                player.move(movement);
              }
            }
        }
      }
    }
  }
}