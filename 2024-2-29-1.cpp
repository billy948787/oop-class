#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if ((i == b && j == a) || i == j) {
                string check;
                check = (i * j > 10) ? "=" : "= ";
                cout << j << '*' << i << check << i * j << " ";
            } else {
                cout << "       ";
            }
        }
        cout << '\n';
    }
}