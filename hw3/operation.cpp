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
      result = Movement::quit;
      break;
    case 'r': {
      result = Movement::reset;
      break;
    }
    case 224: {
#ifdef _WIN32
      input = _getch();
#elif __APPLE__
      initscr();
      cbreak();
      noecho();

      input = getch();

      endwin();
#endif
      switch (input) {
        case 72:
          result = Movement::up;
          break;
        case 75:
          result = Movement::left;
          break;
        case 80:
          result = Movement::down;
          break;
        case 77:
          result = Movement::right;
          break;
        default:
          break;
      }
      break;
    }
    default:
      break;
  }

  return result;
}

void Operation::movePlayerAndPush(Movement movement) {
  Map& map = Map::getInstance();
  // find player
  Object* player = map.player;

  switch (movement) {
    case Movement::up:
      map.detectCollisionAndMove(player, Movement::up, player->row,
                                 player->column);
      break;
    case Movement::left:
      map.detectCollisionAndMove(player, Movement::left, player->row,
                                 player->column);
      break;
    case Movement::down:
      map.detectCollisionAndMove(player, Movement::down, player->row,
                                 player->column);
      break;
    case Movement::right:
      map.detectCollisionAndMove(player, Movement::right, player->row,
                                 player->column);
      break;
    default:
      break;
  }
}