#include <bits/stdc++.h>

using namespace std;

int main() {
    string input;
    cin >> input;

    int left = 0;
    int right = 0;

    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(')
            left++;
        else if (input[i] == ')')
            right++;
    }
    string answer;
    answer = left == right ? "valid" : "invalid";
    cout << answer;
}