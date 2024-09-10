#include <iostream>

using namespace std

class A {
  int h, m, s;

 public:
  A() {}

  A(A &a) {
    this->h = a.h;
    this->m = a.m;
    this->s = a.s;

    cout << "copy constructor" << endl;
  }

  A setH(int h) {
    this->h = h;
    return *this;
  }

  A setM(int m) {
    this->m = m;
    return *this;
  }

  A setS(int s) {
    this->s = s;
    return *this;
  }

  void print() {
    cout << h << ":" << m << ":" << s << endl;
  }
};

int main() {
  A a;
  a.setH(1).setM(2).setS(3).print();
  return 0;
}