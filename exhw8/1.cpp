#include <iostream>

#include "matrix.h"
using namespace std;

int main() {
    bool running = true;
    Matrix a;
    Matrix b;

    int n;
    cout << "Enter the size of the matrix:";
    cin >> n;

    Matrix::setN(n);

    vector<vector<double> > tempa;
    vector<vector<double> > tempb;

    cout << "Enter the elements of the first matrix:";

    for (int i = 0; i < n; i++) {
        vector<double> temp;
        for (int j = 0; j < n; j++) {
            double a;
            cin >> a;
            temp.push_back(a);
        }
        tempa.push_back(temp);
    }
    cout << "Enter the elements of the second matrix:";
    for (int i = 0; i < n; i++) {
        vector<double> temp;
        for (int j = 0; j < n; j++) {
            double a;
            cin >> a;
            temp.push_back(a);
        }
        tempb.push_back(temp);
    }
    a.setMatrix(tempa);
    b.setMatrix(tempb);
    while (running) {
                int action = 1;
        cout << "Enter the action"
             << "\n1. Addition"
             << "\n2. Subtraction"
             << "\n3. Multiplication"
             << "\n4. Exit"
             << "\n";
        cin >> action;

        vector<vector<double> > result;

        switch (action) {
            case 1:
                cout << "Addtion of a and b:\n";

                result = Matrix::addition(a.getMatrix(), b.getMatrix());

                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result[i].size(); j++) {
                        cout << result[i][j] << " ";
                    }
                    cout << "\n";
                }
                break;
            case 2:
                cout << "Subtraction of a and b:\n";

                result = Matrix::subtraction(a.getMatrix(), b.getMatrix());

                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result[i].size(); j++) {
                        cout << result[i][j] << " ";
                    }
                    cout << "\n";
                }
                break;
            case 3:
                cout << "Multiplication of a and b:\n";

                result = Matrix::multiplication(a.getMatrix(), b.getMatrix());

                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result[i].size(); j++) {
                        cout << result[i][j] << " ";
                    }
                    cout << "\n";
                }
                break;
            case 4:
                running = false;
                break;
        }
    }
}