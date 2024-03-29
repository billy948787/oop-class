#ifndef MATRIX_H
#include <iostream>
#include <vector>
using namespace std;

#define MATRIX_H

class Matrix {
   private:
    static int n;
    vector<vector<double> > m;

   public:
    static double getDeterminant(vector<vector<double> >);
    static vector<vector<double> > getSubMatrix(vector<vector<double> >, int, int);
    static vector<vector<double> > getAdj(vector<vector<double> >);
    static vector<vector<double> > transform(vector<vector<double> >);
    void setMatrix(vector<vector<double> >);
    vector<vector<double> > getMatrix();

    static vector<vector<double> > addition(vector<vector<double> >, vector<vector<double> >);
    static vector<vector<double> > subtraction(vector<vector<double> >, vector<vector<double> >);
    static vector<vector<double> > multiplication(vector<vector<double> >, vector<vector<double> >);
    static vector<vector<double> > division(vector<vector<double> >, vector<vector<double> >);
    static vector<vector<double> > divideByConst(vector<vector<double> >, double);
    static vector<vector<double> > getInversedMatrix(vector<vector<double> >);

    static void setN(int);
};

#endif