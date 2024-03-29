#include "matrix.h"

#include <math.h>

#include <vector>
using namespace std;

int Matrix::n = 0;

void Matrix::setMatrix(vector<vector<double> > matrix) {
    this->m = matrix;
}

vector<vector<double> > Matrix::getMatrix() {
    return m;
}

vector<vector<double> > Matrix::addition(vector<vector<double> > a, vector<vector<double> > b) {
    vector<vector<double> > result;
    for (int i = 0; i < a.size(); i++) {
        vector<double> row;
        for (int j = 0; j < a[i].size(); j++) {
            row.push_back(a[i][j] + b[i][j]);
        }
        result.push_back(row);
    }
    return result;
}

vector<vector<double> > Matrix::subtraction(vector<vector<double> > a, vector<vector<double> > b) {
    vector<vector<double> > result;

    for (int i = 0; i < a.size(); i++) {
        vector<double> row;
        for (int j = 0; j < a[i].size(); j++) {
            row.push_back(a[i][j] - b[i][j]);
        }
        result.push_back(row);
    }

    return result;
}

vector<vector<double> > Matrix::multiplication(vector<vector<double> > a, vector<vector<double> > b) {
    vector<vector<double> > result;

    for (int i = 0; i < a.size(); i++) {
        vector<double> row;
        for (int j = 0; j < a[i].size(); j++) {
            double temp = 0;
            for (int k = 0; k < a.size(); k++) {
                temp += a[i][k] * b[k][j];
            }
            row.push_back(temp);
        }

        result.push_back(row);
    }

    return result;
}

vector<vector<double> > Matrix::division(vector<vector<double> > a, vector<vector<double> > b) {
    vector<vector<double> > aInverse = getInversedMatrix(a);

    vector<vector<double> > result = multiplication(aInverse, b);
    return aInverse;
}

double Matrix::getDeterminant(vector<vector<double> > matrix) {
    if (matrix.size() == 1) {
        return matrix[0][0];
    }
    if (matrix.size() == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    } else {
        double result = 0;
        for (int i = 0; i < n; i++) {
            result += matrix[0][i] * getDeterminant(getSubMatrix(matrix, 0, i)) * pow(-1, 0 + i);
        }

        return result;
    }
}

vector<vector<double> > Matrix::getSubMatrix(vector<vector<double> > origin, int row, int column) {
    vector<vector<double> > result;

    for (int i = 0; i < origin.size(); i++) {
        vector<double> temp;
        for (int j = 0; j < origin.size(); j++) {
            if (i != row && j != column) {
                temp.push_back(origin[i][j]);
            }
        }

        if (!temp.empty()) {
            result.push_back(temp);
        }
    }

    return result;
}

void Matrix::setN(int input) {
    Matrix::n = input;
}

vector<vector<double> > Matrix::getAdj(vector<vector<double> > matrix) {
    vector<vector<double> > result;

    for (int i = 0; i < matrix.size(); i++) {
        vector<double> temp;
        for (int j = 0; j < matrix.size(); j++) {
            temp.push_back(pow(-1, i + j) * getDeterminant(getSubMatrix(matrix, i, j)));
        }

        if (!temp.empty()) {
            result.push_back(temp);
        }
    }
    result = transform(result);
    return result;
}

vector<vector<double> > Matrix::transform(vector<vector<double> > matrix) {
    vector<vector<double> > result;
    for (int i = 0; i < matrix.size(); i++) {
        vector<double> row;
        for (int j = 0; j < matrix.size(); j++) {
            row.push_back(0);
        }
        result.push_back(row);
    }
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

vector<vector<double> > Matrix::divideByConst(vector<vector<double> > matrix, const double a) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            matrix[i][j] /= (double)a;
        }
    }
    return matrix;
}

vector<vector<double> > Matrix::getInversedMatrix(vector<vector<double> > matrix) {
    double det = getDeterminant(matrix);

    vector<vector<double> > adj = getAdj(matrix);

    vector<vector<double> > result;

    if (det == 0) {
        for (int i = 0; i < matrix.size(); i++) {
            vector<double> row;

            for (int j = 0; j < matrix.size(); j++) {
                row.push_back(0);
            }

            result.push_back(row);
        }

        return result;
    } else {
        result = divideByConst(adj, det);

        return result;
    }
}