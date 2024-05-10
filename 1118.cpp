#include <bits/stdc++.h>

using namespace std;

short p(short n, short m) {
  if (m > n) return 0;
  if (m <= 0) return 0;
  if (n <= 1) return 1;
  static short dp[1000000001][1000000001] = {};
  if (dp[n][m] != 0) return dp[n][m];

  dp[n][m] = (m * p(n - 1, m) + p(n - 1, m - 1)) % 2;

  return dp[n][m];
}

int main() {
  int cases;

  cin >> cases;

  while (cases--) {
    int n, m;
    cin >> n >> m;

    short result = p(n, m);

    // cout << result << " ";

    cout << result << "\n";
  }
}