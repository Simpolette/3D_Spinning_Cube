#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>

class Matrix{

private:
    int row;
    int col;
    double* matrix;

public:
    Matrix();
    Matrix(int row, int col);
    Matrix(const Matrix& matrix);
    Matrix(double x, double y, double z);
    ~Matrix();
    double& operator [] (int idx);
    Matrix operator * (const Matrix& other);
    Matrix& operator = (const Matrix& other);
    Gdiplus::PointF to2D(double focal, Gdiplus::PointF origin);
    void print() const;
};

#endif