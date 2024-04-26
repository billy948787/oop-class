#include <bits/stdc++.h>

#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(0);                       \
  cout.tie(0)

using namespace std;

long long calculate(long long n) {
  long long answer = 0;

  if (n > sqrt(LLONG_MAX)) return LLONG_MAX;
  answer = (long long)((1 + n) * n) / 2;

  return answer;
}

int main() {
  fastio;
  int cases;
  cin >> cases;

  for (int ca = 1; ca <= cases; ca++) {
    int city;
    long long road;
    int answer = 0;

    cin >> city >> road;

    if (road == city - 1)
      answer = road;
    else if (road < city - 1)
      answer = 0;
    else {
      for (int i = city; i >= 1; i--) {
        if (road - calculate(i) - (city - i - 1) <= 0)
          answer = city - i - 1;
        else
          break;
      }
    }

    cout << answer << "\n";
  }
}