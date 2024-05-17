#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

int main() {
  fstream file;
  file.open("text.txt", ios::in);

  if (!file) {
    cout << "File not created!";
    return 0;
  }

  map<string, int> data;

  string input;

  while (file >> input) {
    if ((input.back() > 'Z' || input.back() < 'A') &&
        (input.back() > 'z' || input.back() < 'a'))
      input.erase(input.size() - 1);
    if ((input.front() > 'Z' || input.front() < 'A') &&
        (input.front() > 'z' || input.front() < 'a'))
      input.erase(0);

    if (data.count(input)) {
      data[input]++;
    } else if (!data.count(input)) {
      data[input] = 1;
    }
  }

  file.close();

  file.open("answer.txt", ios::out);

  for (auto p : data) {
    if ((p.first > "A" && p.first < "Z") || (p.first > "a" && p.first < "z"))
      cout << p.first << " " << "有" << p.second << "個\n";
    file << p.first << " " << "有" << p.second << "個\n";
  }

  file.close();
}