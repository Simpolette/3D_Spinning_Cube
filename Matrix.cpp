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

double Matrix::convertDegToRad(double degree){
    return degree * M_PI / 180;
}

Matrix Matrix::getXRotationMatrix(double angle){
    Matrix matrix(3, 3);
    angle = convertDegToRad(angle);

    // [0][0]
    matrix[3 * 0 + 0] = 1;
    // [1][1]
    matrix[3 * 1 + 1] = cos(angle);
    // [2][2]
    matrix[3 * 2 + 2] = cos(angle);
    // [1][2]
    matrix[3 * 1 + 2] = -sin(angle);
    // [2][1]
    matrix[3 * 2 + 1] = sin(angle);
    
    return matrix;
}

Matrix Matrix::getYRotationMatrix(double angle){
    Matrix matrix(3, 3);
    angle = convertDegToRad(angle);

    // [0][0]
    matrix[3 * 0 + 0] = cos(angle);
    // [1][1]
    matrix[3 * 1 + 1] = 1;
    // [2][2]
    matrix[3 * 2 + 2] = cos(angle);
    // [0][2]
    matrix[3 * 0 + 2] = sin(angle);
    // [2][0]
    matrix[3 * 2 + 0] = -sin(angle);

    return matrix;
}

Matrix Matrix::getZRotationMatrix(double angle){
    Matrix matrix(3, 3);
    angle = convertDegToRad(angle);

    // [0][0]
    matrix[3 * 0 + 0] = cos(angle);
    // [1][1]
    matrix[3 * 1 + 1] = cos(angle);
    // [2][2]
    matrix[3 * 2 + 2] = 1;
    // [0][1]
    matrix[3 * 0 + 1] = -sin(angle);
    // [1][0]
    matrix[3 * 1 + 0] = sin(angle);

    return matrix;
}

Gdiplus::PointF Matrix::to2D(double focal, Gdiplus::PointF origin){
    Matrix point2D(*this);
    point2D = getXRotationMatrix(35.264) * getYRotationMatrix(45) * point2D;
    return Gdiplus::PointF(point2D[0] + origin.X, point2D[1] + origin.Y);
}

void Matrix::print() const {
    std::cout << row << " " << col << '\n';
    for (int i = 0; i < row * col; i++){
        std::cout << matrix[i] << " ";
    }
}