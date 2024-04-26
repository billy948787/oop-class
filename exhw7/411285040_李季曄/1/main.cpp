#include <cmath>
#include <iostream>

using namespace std;

int main() {
  int h, m;

  double hourDegree = 0;
  double minuteDegree = 0;

  double degree = 0;

  while (cin >> h >> m) {
    if (h >= 12) h -= 12;
    hourDegree = (h * 30) + (m * 0.5);

    minuteDegree = m * 6;

    degree = abs(minuteDegree - hourDegree);

    if (degree > 180) degree = 360 - degree;

    printf("%.0f\n", degree);
  }
}