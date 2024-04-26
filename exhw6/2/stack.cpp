#include "stack.h"

#include <cstdlib>
#include <ctime>

Stack::Stack(int n) {
  this->n = n;
  this->_front = new int[n + 1];
  this->_back = _front;
  std::vector<int> record;

  srand(time(0));
  for (int i = 0; i < n; i++) {
    bool isRepeat = false;
    int random = rand() % 52;
    for (int j = 0; j < record.size(); j++) {
      if (record[j] == random) {
        isRepeat = true;
        i--;
        continue;
      }
    }
    if (isRepeat) continue;
    record.push_back(random);
    push(random);
  }

}

Stack::Stack(std::string inputs) {
  this->_front = new int[52];
  this->_back = _front;
  std::vector<int> temp;

  for (int index = 0; index < inputs.size(); index++) {
    char element = inputs[index];
    if (element == ' ') {
      int result = 0;
      if (temp.empty()) continue;
      for (int i = 0; i < temp.size(); i++) {
        result += temp[i] * pow(10, (temp.size() - i - 1));
      }

      temp.clear();

      push(result);
    }

    else {
      temp.push_back(element - 48);
    }
    if (index == inputs.size() - 1) {
      int result = 0;
      if (temp.empty()) continue;
      for (int i = 0; i < temp.size(); i++) {
        result += temp[i] * pow(10, (temp.size() - i - 1));
      }

      temp.clear();
      push(result);
    }
  }
}

Stack::~Stack() { delete[] _front; }

void Stack::push() {
  int input;
  if (_back - _front > 10) {
    std::cout << "The stack is full\n";
    return;
  }
  std::cout << "Please enter a number\n";
  std::cin >> input;

  this->_back += 1;
  *(this->_back) = input;

  int* temp = this->_back;

  std::cout << "The stack is:\n";

  while (temp != _front) {
    std::cout << *temp << "\n";

    temp--;
  }
}

void Stack::push(int input) {
  // if (_back - _front > 52) {
  //   std::cout << "The stack is full\n";
  //   return;
  // }
  this->_back += 1;

  *(this->_back) = input;
}

void Stack::pop() {
  if (_back == _front) {
    std::cout << "The stack is empty\n";
    return;
  }

  top();

  this->_back--;

  // int* temp = _back;

  // std::cout << "The stack is:\n";

  // while (temp != _front) {
  //   std::cout << *temp << "\n";
  //   temp--;
  // }
}

void Stack::top() {
  if (_back == _front) {
    std::cout << "The stack is empty\n";
    return;
  }

  int suit = (*(this->_back) / 13) + 1;

  int number = (*(this->_back) % 13) + 1;

  std::cout << "The top card is: ";

  switch (number) {
    case 1:
      std::cout << "A";
      break;
    case 11:
      std::cout << "J";
      break;
    case 12:
      std::cout << "Q";
      break;
    case 13:
      std::cout << "K";
      break;
    default:
      std::cout << number;
      break;
  }

  std::cout << " of ";

  switch (suit) {
    case 1:
      std::cout << "Spades\n";
      break;
    case 2:
      std::cout << "Hearts\n";
      break;
    case 3:
      std::cout << "Clubs\n";
      break;
    case 4:
      std::cout << "Diamonds\n";
      break;
  }
}

void Stack::empty() {
  _back = _front;
  std::cout << "Empty the stack!\n";
}

void Stack::shuffle() {
  srand(time(0));
  for (int i = 0; i < n; i++) {
    int random = rand() % (_back - _front);

    int temp = *(_front + i + 1);

    *(_front + 1 + i) = *(_front + random + 1);

    *(_front + random + 1) = temp;
  }

  int* temp = _back;

  while (temp != _front) {
    showCard(*temp);
    temp--;
  }
}

void Stack::showCard(int num) {
  int suit = (num / 13) + 1;
  int number = (num % 13) + 1;

  switch (number) {
    case 1:
      std::cout << "A";
      break;
    case 11:
      std::cout << "J";
      break;
    case 12:
      std::cout << "Q";
      break;
    case 13:
      std::cout << "K";
      break;
    default:
      std::cout << number;
      break;
  }

  std::cout << " of ";

  switch (suit) {
    case 1:
      std::cout << "Spades\n";
      break;
    case 2:
      std::cout << "Hearts\n";
      break;
    case 3:
      std::cout << "Clubs\n";
      break;
    case 4:
      std::cout << "Diamonds\n";
      break;
  }
}