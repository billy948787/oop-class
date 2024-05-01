#include <bits/stdc++.h>

#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(0);                       \
  cout.tie(0)

using namespace std;

int main() {
  fastio;
  int l, n;

  cin >> l >> n;

  vector<pair<string, string>> irregular;

  vector<string> regular;

  for (int i = 0; i < l; i++) {
    string input;
    string input2;
    cin >> input >> input2;

    pair<string, string> p;

    p.first = input;
    p.second = input2;

    irregular.push_back(p);
  }

  for (int i = 0; i < n; i++) {
    string input;
    cin >> input;

    if (input.back() == 'y') {
      input.pop_back();
      input = input + "ies";
    } else if (input.back() == 'o' || input.back() == 's' ||
               (input[input.size() - 2] == 'c' &&
                input[input.size() - 1] == 'h') ||
               (input[input.size() - 2] == 's' &&
                input[input.size() - 1] == 'h') ||
               input.back() == 'x') {
      input = input + "es";
    } else {
      input.push_back('s');
    }
    regular.push_back(input);
  }

  for (auto p : irregular) {
    cout << p.second << "\n";
  }

  for (auto e : regular) {
    cout << e << "\n";
  }
}