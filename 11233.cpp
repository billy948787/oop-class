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

  map<string, string> answers;

  vector<string> inputs;

  for (int i = 0; i < l; i++) {
    string input;
    string input2;
    cin >> input >> input2;

    pair<string, string> p;

    answers[input] = input2;
  }

  for (int i = 0; i < n; i++) {
    string input;
    cin >> input;

    inputs.push_back(input);

    string ans = input;
    // check
    if (answers.count(input) == 1) continue;

    if (ans.back() == 'y' && ans[ans.size() - 2] != 'a' &&
        ans[ans.size() - 2] != 'e' && ans[ans.size() - 2] != 'i' &&
        ans[ans.size() - 2] != 'o' && ans[ans.size() - 2] != 'u') {
      ans.pop_back();
      ans = ans + "ies";
    } else if (ans.back() == 'o' || ans.back() == 's' ||
               (ans[ans.size() - 2] == 'c' && ans[ans.size() - 1] == 'h') ||
               (ans[ans.size() - 2] == 's' && ans[ans.size() - 1] == 'h') ||
               ans.back() == 'x') {
      ans = ans + "es";
    } else {
      ans.push_back('s');
    }

    answers[input] = ans;
  }

  for (auto element : inputs) {
    cout << answers[element] << "\n";
  }
}