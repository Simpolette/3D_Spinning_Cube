#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>

class Matrix{

private:
    int row;
    int col;
    double* matrix;

public:
    Matrix(int row, int col);
    Matrix(const Matrix& matrix);
    ~Matrix();
    double& operator [] (int idx);
    Matrix operator * (const Matrix& other);
};

#endif