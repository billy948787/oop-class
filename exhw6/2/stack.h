#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>
#include <math.h>
class Stack {
 private:
  int* _front;
  int* _back;
  int n;

 public:
  Stack(std::string);
  Stack(int);
  ~Stack();
  void pop();
  void shuffle();
  void showCard(int);
  void push();
  void push(int);
  void empty();
  void top();
};

#endif