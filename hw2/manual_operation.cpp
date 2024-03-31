#include "manual_operation.h"
#include <iostream>

bool ManualOperation::insurance() {
  std::string input;
  std::cout
      << "Beacause the banker has shown an A. Do you want to take "
         "insurace?\n"
      << "1 for yes(You need to wager half of your bet amount.)\n0 for no\n";
  while (true) {
    std::cin >> input;
    if (input != "1" && input != "0") {
      std::cout << "Please enter valid number!\n";
      continue;
    }

    if (input == "1") {
      std::cout << "You have taken the insurance\n";
      return true;
    } else {
      std::cout << "You chose not to take the insurance\n";
      return false;
    }
    break;
  }
}

bool ManualOperation::hit(int point) {
  std::string input;
  std::cout << "Do you want to hit a card?\n"
            << "1 for yes\n"
            << "0 for no\n";
  while (true) {
    std::cin >> input;
    if (input != "1" && input != "0") {
      continue;
    }

    return (input == "1") ? true : false;
  }
}

std::map<std::string, bool> ManualOperation::doubleOrSurrender(int point) {
  std::string input;
  std::map<std::string, bool> result;
  result["double"] = false;
  result["surrender"] = false;
  bool isEleven = (point == 11);
  (isEleven) ? std::cout << "Which action do you want to take?\n"
                         << "1 for surrender(take back half of your bet)\n"
                         << "0 for nothing and continue\n"
             : std::cout << "Which action do you want to take?\n"
                         << "1 for double down(Beacause your point is 11. "
                         << "It can only take one more card)\n"
                         << "2 for surrender(take back half of your bet)\n";
  while (true) {
    std::cin >> input;

    if (isEleven) {
      if (input != "0" && input != "1" && input != "2") {
        std::cout << "Please enter valid number!\n";
        continue;
      } else {
        if (input == "1") {
          result["double"] = true;
        } else if (input == "2") {
          result["surrender"] = true;
        }
      }
    } else {
      if (input != "0" && input != "1") {
        std::cout << "Please enter valid number!\n";
        continue;
      } else {
        if (input == "1") {
          result["surrender"] = true;
        }
      }
    }
    return result;
    break;
  }
}

int ManualOperation::stake(int money) {
  std::string input;
  std::cout << "How much money do you want to hit : \n";
  while (true) {
    std::cin >> input;
    bool isValid = true;
    // check if valid
    for (auto element : input) {
      if (element > 57 || element < 48) {
        "Please enter valid number!\n";
        isValid = false;
        break;
      }
    }

    if (!isValid) {
      continue;
    }

    int number = std::stoi(input);

    return number;
  }
}
