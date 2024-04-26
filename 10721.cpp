#include <bits/stdc++.h>

#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(0);                       \
  cout.tie(0)

using namespace std;

bool check(vector<bool> codes, int n, int k, int m) {
  bool bars = false, wides = false;

  int b = 0, w = 0;

  vector<int> records;

  for (auto element : codes) {
    if (element) {
      wides = (w <= m);
      records.push_back(w);
      w = 0;
      b++;
    } else {
      wides = (b <= m);
      records.push_back(b);
      b = 0;
      w++;
    }
  }

  bars = (records.size() == k);

  return bars && wides;
}

int place(vector<bool> codes, int dp[], int n, int k, int m, int index) {
  if (index == n) {
    if (check(codes, n, k, m))
      return 1;
    else
      return 0;
  }

  if (dp[index] != 0) return dp[index];

  vector<bool> sub1 = codes;
  sub1.push_back(true);
  vector<bool> sub2 = codes;
  sub2.push_back(false);

  dp[index] = place(sub1, dp, n, k, m, index + 1) + place(sub2, dp, n, k, m, index + 1);
  return dp[index];
}

int main() {
  fastio;
  int n, k, m;

  while (cin >> n >> k >> m) {
    vector<bool> codes;

    codes.push_back(true);

    int dp[200000] = {};

    cout << place(codes, dp, n, k, m, 1) << "\n";
  }
}