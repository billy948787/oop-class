

#include <iostream>
#include "stack.h"

int main() {
  int n;
  std::cout << "How many pokers do you want?\n";

  std::cin >> n;

  Stack poker(n);

  bool isRunning = true;

  while(isRunning){
    std::cout << "Please enter a number\n";
    std::cout << "1. deal\n";
    std::cout << "2. shuffle\n";
    std::cout << "0. quit\n";

    int input;
    std::cin >> input;

    switch(input){
      case 1:
        poker.pop();
        break;
      case 2:
        poker.shuffle();
        break;
      case 0:
        isRunning = false;
        break;
      default:
        std::cout << "Invalid input\n";
    }
  }
  return 0;
}