#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  fstream file;
  file.open("basic.txt", ios::in);
  if (!file) {
    cout << "File not created!";
    return 0;
  }

  map<string, vector<string> > data;

  string name, height, weight, sex, age;

  while (file >> name >> height >> weight >> sex >> age) {
    vector<string> key;
    key.push_back(name);
    key.push_back(height);
    key.push_back(weight);
    key.push_back(sex);
    key.push_back(age);

    data[name] = key;
  }

  file.close();

  string input;
  cout << "please enter a name\n";
  cin >> input;

  vector<string> result = data[input];

  file.open("output.txt", ios::out);

  for (auto element : result) {
    cout << element << " ";
    file << element << " ";
  }

  file.close();
}