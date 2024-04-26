#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<string> vincent;
  vector<string> leo;
  vector<string> invitee;

  string input;
  cout << "vincent's friend : \n";
  while (true) {
    cin >> input;

    if (input == "0") break;

    vincent.push_back(input);
  }
  cout << "leo's friend : \n";
  while (true) {
    cin >> input;

    if (input == "0") break;

    leo.push_back(input);
  }

  cout << "invitee : \n";

  for (auto name : vincent) {
    invitee.push_back(name);
  }

  for (auto name : leo) {
    invitee.push_back(name);

    for (int i = 0; i < invitee.size() - 1; i++) {
      if (invitee[i] == name) invitee.pop_back();
    }
  }

  for (auto name : invitee) {
    cout << name << "\n";
  }
}