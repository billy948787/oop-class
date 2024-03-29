#include <iostream>

using namespace std;

bool checkSubsequence(string a, string b) {
    int i = 0;
    for (int j = 0; j < b.size(); j++) {
        if (a[i] == b[j]) i++;
        if (i == a.size()) return true;
    }
    return false;
}

int main() {
    while (true) {
        string a, b;
        cin >> a >> b;
        if (a == "0" && b == "0") break;

        cout << (checkSubsequence(a, b) ? "true" : "false") << '\n';
    }
}