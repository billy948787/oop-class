#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int toInt(string s) {
  int result = 0;
  for (int i = 0; i < s.size(); i++) {
    result += (s[i] - '0') * pow(10, s.size() - i - 1);
  }
  return result;
}

int main() {
  fstream file("text.txt", ios::in);

  vector<string> data;
  string line;

  while (file >> line) {
    data.push_back(line);
  }

  file.close();

  file.open("output.txt", ios::out);

  vector<int> result;

  for (auto line : data) {
    string numbers;
    for (auto c : line) {
      if (c >= '0' && c <= '9') {
        numbers.push_back(c);
      } else {
        if (numbers.size() > 0) {
          result.push_back(toInt(numbers));
          numbers.clear();
        }
      }
    }
    if (numbers.size() > 0) {
      result.push_back(toInt(numbers));
    }
  }

  sort(result.begin(), result.end());

  for (auto i : result) {
    cout << i << " ";
    file << i << " ";
  }

  file.close();
}