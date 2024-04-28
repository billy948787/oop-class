#include <bits/stdc++.h>

#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(0);                       \
  cout.tie(0)

using namespace std;

int minimumDistance(vector<int> street, int home) {
  int result = 0;
  for (auto element : street) {
    result += abs(home - element);
  }

  return result;
}

int middle(vector<int> street) {
  int result = 0;
  for (int i = 0; i < street.size(); i++) {
    if (i == street.size() / 2) result = street[i];
  }
  return result;
}

int main() {
  fastio;

  int cases;
  cin >> cases;

  while (cases--) {
    int streets;
    int answer = 1e9;
    cin >> streets;

    vector<int> street;

    for (int i = 0; i < streets; i++) {
      int input;
      cin >> input;

      street.push_back(input);
    }

    sort(street.begin(), street.end());

    int home = middle(street);

    // cout << home << " ";

    answer = minimumDistance(street, home);

    cout << answer << "\n";
  }
}