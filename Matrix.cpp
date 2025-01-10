#include "Matrix.h"

Matrix::Matrix(){
    row = 0;
    col = 0;
    matrix = NULL;
}

Matrix::Matrix(int row, int col) : row(row), col(col){
    matrix = new double[row * col];
    for (int i = 0; i < row * col; i++){
        matrix[i] = 0;
    }
}

Matrix::Matrix(double x, double y, double z){
    row = 3;
    col = 1;
    matrix = new double[3];
    matrix[0] = x;
    matrix[1] = y;
    matrix[2] = z;
}

Matrix::Matrix(const Matrix& other) : row(other.row), col(other.col){
    matrix = new double[row * col];
    for (int i = 0; i < row * col; i++){
        matrix[i] = other.matrix[i];
    }
}

Matrix::~Matrix(){
    delete[] matrix;
}

double& Matrix::operator [] (int idx){
    if (idx < row * col && idx >= 0){
        return matrix[idx];
    }
    throw std::out_of_range("Index out of range");
}

Matrix Matrix::operator * (const Matrix& other){
    Matrix res(this->row, other.col);
    for (int i = 0; i < res.row; i++){
        for (int j = 0; j < res.col; j++){
            for (int k = 0; k < this->col; k++){
                res.matrix[res.col * i + j] += matrix[col * i + k] * other.matrix[other.col * k + j];
            }
        }
    }
    return res;
}

Matrix& Matrix::operator = (const Matrix& other){
    if (this != &other){
        row = other.row;
        col = other.col;
        matrix = new double[row * col];
        for (int i = 0; i < row * col; i++){
            matrix[i] = other.matrix[i];
        }
    }
    return *this;
}

Gdiplus::PointF Matrix::to2D(double focal, Gdiplus::PointF origin){
    double x = sqrt(2) / 2 * (this->matrix[0] + this->matrix[2]) + origin.X;
    double y = 1 / sqrt(6) * this->matrix[0] +
            sqrt(0.5) * this->matrix[1] - 1 / sqrt(6) * this->matrix[2] + origin.Y;
    return Gdiplus::PointF(x, y);
}

void Matrix::print() const {
    std::cout << row << " " << col << '\n';
    for (int i = 0; i < row * col; i++){
        std::cout << matrix[i] << " ";
    }
}