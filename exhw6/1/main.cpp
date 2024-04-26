#include <iostream>
#include <vector>

#include "stack.h"

int main() {
  std::string inputs;

  std::cout << "Please enter numbers:\n";
  std::getline(std::cin, inputs);

  Stack stack(inputs);

  int input;
  bool isRunning = true;

  while (isRunning) {
    std::cout << "Please enter what you would like to do:\n";
    std::cout << "1. Push\n";
    std::cout << "2. Pop\n";
    std::cout << "3. Top\n";
    std::cout << "4. Empty\n";
    std::cout << "0. Exit\n";

    std::cin >> input;

    switch (input) {
      case 1:
        stack.push();
        break;
      case 2:
        stack.pop();
        break;
      case 3:
        stack.top();
        break;
      case 4:
        stack.empty();
        break;
      case 0:
        isRunning = false;
        break;
    }
  }
}