#include <iostream>

using namespace std;

int combination(int money, int coin) {
    static int dp[504];
    if (money < 0) return 0;
    if (money == 0) return 1;
    

    if (coin == 50)
        return combination(money - 1, 1) + combination(money - 5, 5) + combination(money - 10, 10) + combination(money - 50, 50);
    else if (coin == 10)
        return combination(money - 1, 1) + combination(money - 5, 5) + combination(money - 10, 10);
    else if (coin == 5)
        return combination(money - 1, 1) + combination(money - 5, 5);
    else
        return combination(money - 1, 1);
}

int main() {
    while (true) {
        int money;
        cin >> money;
        if (money == 0) break;

        cout << combination(money, 50) << '\n';
    }
}