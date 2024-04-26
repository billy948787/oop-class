#include "stack.h"

Stack::Stack(std::string inputs) {
  this->_front = new int[50];
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
      if(temp.empty()) continue;
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
  if (_back - _front > 10) {
    std::cout << "The stack is full\n";
    return;
  }
  this->_back += 1;

  *(this->_back) = input;
}

void Stack::pop() {
  if (_back == _front) {
    std::cout << "The stack is empty\n";
    return;
  }

  this->_back--;

  int* temp = _back;

  std::cout << "The stack is:\n";

  while (temp != _front) {
    std::cout << *temp << "\n";
    temp--;
  }
}

void Stack::top() {
  if (_back == _front) {
    std::cout << "The stack is empty\n";
    return;
  }

  std::cout << "The top is : " << *_back << "\n";
}

void Stack::empty() {
  _back = _front;
  std::cout << "Empty the stack!\n";
}