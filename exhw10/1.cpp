#include <iostream>

using namespace std;

int main() {
  while (1) {
    string input;
    getline(cin, input);

    if (input == "0") break;

    int size = 0;

    for (int i = 0; i < input.size(); i++) {
      size++;
      if (input[i] == ' ') {
        size = 0;
      }
    }

    cout << size << endl;
  }
}