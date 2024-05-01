#include <bits/stdc++.h>

#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(0);                       \
  cout.tie(0)

using namespace std;

int main() {
  fastio;
  double roof, climb, slide, decayRatio;

  while (true) {
    cin >> roof >> climb >> slide >> decayRatio;
    double now = 0;
    double firstClimb = climb;
    int day = 0;

    if (roof == 0) break;

    while (true) {
      now += climb;

      if (now > roof) {
        cout << "success on day " << day + 1 << "\n";
        break;
      }

      now -= slide;

      if (now < 0) {
        cout << "failure on day " << day + 1 << "\n";
        break;
      }

      climb -= firstClimb * (decayRatio / 100);

      if (climb < 0) climb = 0;
      day++;
    }
  }
}