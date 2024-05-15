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

  initscr();
  cbreak();
  noecho();

  input = getch();

  endwin();

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