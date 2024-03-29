#include <iostream>

using namespace std;

bool check(string s) {
    if (s.length() != 10)
        return false;
    if (s[0] < 65 || s[0] > 90)
        return false;

    if (s[1] != '1' && s[1] != '2')
        return false;

    return true;
}

int main() {
    string input;

    cout << "Please enter an ID number:";
    cin >> input;

    cout << (check(input) ? "Correct" : "Incorrect");
}