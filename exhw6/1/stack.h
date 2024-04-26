#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>
#include <math.h>

class Stack {
 private:
  int* _front;
  int* _back;

 public:
  Stack(std::string);
  ~Stack();
  void pop();
  void push();
  void push(int);
  void empty();
  void top();
};

#endif