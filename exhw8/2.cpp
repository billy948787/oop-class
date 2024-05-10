#include <bits/stdc++.h>

using namespace std;

bool close(vector<bool> area, int totalM) {
  int count = 0;

  area[0] = false;

  int i = 0;
  int lastCount = count;
  while (true) {
    int m = totalM;
    for (int j = 1; j <= m; j++) {
      if (i + j < area.size()) {
        // tell if power is off
        if (!area[i + j]) {
          j = j - 1;
          i++;
          continue;
        }
        // turn off the power
        if (j == m) {
          // if the next step is the 13th area
          if (i + m == 12) return false;

          area[i + m] = false;
          i += m;
          count++;
          continue;
        }
      } else {
        for (int k = 0; k < area.size(); k++) {
          if (area[k] && j == m) {
            i = k;
            area[k] = false;
            m = 0;
            count++;
            break;
          }
          if (area[k]) {
            i = k;
            break;
          }
        }

        m -= j;
        j = 0;
        continue;
      }
    }

    if (count == area.size() - 1)
      return true;
    else if (lastCount == count)
      return false;
    else {
      lastCount = count;
    }
  }
}

int find(int n, int m, vector<bool> area) {
  if (m >= n) return 0;

  if (close(area, m))
    return m;
  else
    return find(n, m + 1, area);
}

int main() {
  int n;
  while (true) {
    cin >> n;
    if (n == 0) break;

    vector<bool> area(n, true);

    int result = find(n, 2, area);

    if (result == 0)
      cout << "no answer\n";
    else
      cout << result << "\n";
  }
}