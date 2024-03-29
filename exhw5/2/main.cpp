#include <iostream>

using namespace std;

int main() {
    string input;
    while (1) {
        cin >> input;
        if (input == "0") {
            break;
        }

        int paremtheses = 0;
        int squareBrackets = 0;
        int curlyBrackets = 0;

        int lookingForParetheses = 0;
        int lookingForSquareBrackets = 0;
        int lookingForCurlyBrackets = 0;

        for (int i = 0; i < input.size(); i++) {
            if (input[i] == '(') {
                lookingForParetheses += 1;
            } else if (input[i] == ')' && lookingForParetheses > 0) {
                lookingForParetheses -= 1;
            } else if (input[i] == ')' && lookingForParetheses <= 0) {
                paremtheses++;
            } else if (lookingForParetheses && i == input.size() - 1) {
                paremtheses += lookingForParetheses;
            }

            if (input[i] == '[') {
                lookingForSquareBrackets += 1;
            } else if (input[i] == ']' && lookingForSquareBrackets > 0) {
                lookingForSquareBrackets -= 1;
            } else if (input[i] == ']' && lookingForSquareBrackets <= 0) {
                squareBrackets++;
            } else if (lookingForSquareBrackets && i == input.size() - 1) {
                squareBrackets += lookingForSquareBrackets;
            }

            if (input[i] == '{') {
                lookingForCurlyBrackets += 1;
            } else if (input[i] == '}' && lookingForCurlyBrackets > 0) {
                lookingForCurlyBrackets -= 1;
            } else if (input[i] == '}' && lookingForCurlyBrackets <= 0) {
                curlyBrackets++;
            } else if (lookingForCurlyBrackets && i == input.size() - 1) {
                curlyBrackets += lookingForCurlyBrackets;
            }
        }

        cout << "paremtheses: " << paremtheses << "\n"
             << "squareBrackets: " << squareBrackets << "\n"
             << "curlyBrackets: " << curlyBrackets << "\n";
    }
}