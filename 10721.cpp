#include <bits/stdc++.h>

using namespace std;

// bool check(vector<bool> codes, int n, int k, int m) {
//   bool bars = false, wides = false;

//   int b = 0, w = 0;

//   vector<int> records;

//   for (int i = 0; i < codes.size(); i++) {
//     bool element = codes[i];
//     if (element) {
//       if (w > 0) records.push_back(w);
//       w = 0;
//       b++;
//     } else {
//       if (b > 0) records.push_back(b);
//       b = 0;
//       w++;
//     }
//     wides = (w <= m) && (b <= m);

//     if (!wides) return false;

//     if (i == codes.size() - 1) {
//       if (w > 0) records.push_back(w);
//       if (b > 0) records.push_back(b);
//     }
//   }

//   bars = (records.size() == k);

//   return bars && wides;
// }

long long place(vector<bool> codes, long long ***dp, int n, int k, int m,
                int index, int conB, int conW, int unique) {
  if (index > n) return 0;

  if (conB > m || conW > m) return 0;

  if (conB + conW > n) return 0;

  if (k - unique > n - index) return 0;

  if (unique > k) return 0;

  if (index == n) {
    if (unique == k) {
      return 1;
    } else {
      return 0;
    }
  }
  if (dp[unique][index][conB + conW] != 0)
    return dp[unique][index][conB + conW];

  vector<bool> sub1 = codes;
  sub1.push_back(true);
  vector<bool> sub2 = codes;
  sub2.push_back(false);

  dp[unique][index][conB + conW] =
      place(sub1, dp, n, k, m, index + 1, conB + 1, 0,
            (conB > 0) ? unique : unique + 1) +
      place(sub2, dp, n, k, m, index + 1, 0, conW + 1,
            (conW > 0) ? unique : unique + 1);

  return dp[unique][index][conB + conW];
}

int main() {
  int n, k, m;

  long long ***dp = new long long **[60];
  for (int i = 0; i < 60; i++) {
    dp[i] = new long long *[60];
    for (int j = 0; j < 60; j++) {
      dp[i][j] = new long long[60];
    }
  }

  while (cin >> n >> k >> m) {
    for (int i = 0; i < 60; i++) {
      for (int j = 0; j < 60; j++) {
        for (int k = 0; k < 60; k++) {
          dp[i][j][k] = 0;
        }
      }
    }
    vector<bool> codes;

    codes.push_back(true);

    cout << place(codes, dp, n, k, m, 1, 1, 0, 1) << "\n";
  }

  for (int i = 0; i < 60; i++) {
    for (int j = 0; j < 60; j++) {
      delete[] dp[i][j];
    }
    delete[] dp[i];
  }
  delete[] dp;
}