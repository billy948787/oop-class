#include <bits/stdc++.h>

using namespace std;

int find(int input) {
  int result = 0;
  int mul = 1;
  while (input - result < 0) {
    result = mul * -2;
    mul++;
  }

  return mul - 1;
}

int main() {
  int cases;
  cin >> cases;

  for (int ca = 1; ca <= cases; ca++) {
    int input;
    vector<int> result;
    cin >> input;
    if (input == 0) result.push_back(0);

    while (input != 0) {
      if (input < 0) {
        result.push_back(input - find(input) * -2);
        input = find(input);
      } else {
        result.push_back(input % -2);
        input /= -2;
      }
    }

    reverse(result.begin(), result.end());

    printf("Case #%d: ", ca);
    for (auto element : result) {
      printf("%d", element);
    }

    cout << "\n";
  }
}