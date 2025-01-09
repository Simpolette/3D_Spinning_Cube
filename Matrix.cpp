#include "Matrix.h"

Matrix::Matrix(int row, int col) : row(row), col(col){
    matrix = new double[row * col];
    for (int i = 0; i < row * col; i++){
        matrix[i] = 0;
    }
}

Matrix::~Matrix(){
    delete matrix;
}

double& Matrix::operator [] (int idx){
    if (idx < row * col && idx >= 0){
        return matrix[idx];
    }
    throw std::out_of_range("Index out of range");
}

Matrix Matrix::operator * (const Matrix& other){
    Matrix matrix(this->row, other.col);
    for (int i = 0; i < matrix.row; i++){
        for (int j = 0; j < matrix.col; j++){
            for (int k = 0; k < this->col; k++){
                matrix[matrix.row * i + j] = this->matrix[this->row * i + k] + other.matrix[other.row * k + j];
            }
        }
    }
    return matrix;
}