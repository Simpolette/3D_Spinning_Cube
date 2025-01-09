#include "Cube.h"

Cube::Cube(){
    points = NULL;
    origin = Gdiplus::PointF(0, 0);
    focal = 500;
}

Cube::Cube(const Gdiplus::PointF& origin){
    this->origin = origin;    
    focal = 500;
    points = new Point3D[SQUARE_SIDES];

    // Initalize the top face of the cube
    points[0] = Point3D(0, 0, SIDE_LENGTH);
    points[1] = Point3D(SIDE_LENGTH, 0, SIDE_LENGTH);
    points[2] = Point3D(SIDE_LENGTH, SIDE_LENGTH, SIDE_LENGTH);
    points[3] = Point3D(0, SIDE_LENGTH, SIDE_LENGTH);
}

Cube::~Cube(){
    delete points;
}

std::vector <Gdiplus::PointF*> Cube::calFaces(){
    std::vector <Gdiplus::PointF*> faces;
    
    // Top face
    Gdiplus::PointF* topFace = new Gdiplus::PointF[SQUARE_SIDES];
    for (int i = 0; i < SQUARE_SIDES; i++){
        topFace[i] = points[i].to2D(focal, origin);
    }

    faces.push_back(topFace);

    // // Bottom face
    // Gdiplus::PointF* bottomFace = new Gdiplus::PointF[SQUARE_SIDES];
    // for (int i = 0; i < SQUARE_SIDES; i++){
    //     bottomFace[i] = Gdiplus::PointF(topFace[i].X, topFace[i].Y + SIDE_LENGTH);
    // }

    // // Middle faces
    // for (int i = 0; i < SQUARE_SIDES; i++){
    //     Gdiplus::PointF* middleFace = new Gdiplus::PointF[SQUARE_SIDES];
    //     for (int j = 0; j < SQUARE_SIDES; j++){
    //         if (j < 2){
    //             // 2 points on top
    //             middleFace[j] = topFace[(j + i) % 4];
    //         }
    //         else{
    //             // 2 points at bottom
    //             middleFace[j] = bottomFace[(j + i - 2) % 4];
    //         }
    //     }
    //     // Swapping 2 points for correct order
    //     std::swap(middleFace[2], middleFace[3]);
    //     faces.push_back(middleFace);
    // }

    // faces.push_back(bottomFace);

    return faces;
}

// Point3D Cube::convert2Dto3D(const Gdiplus::PointF& point2D){

// }

double Cube::convertDegToRad(double degree){
    return degree * M_PI / 180;
}

Matrix Cube::getXRotationMatrix(double angle){
    Matrix matrix(3, 3);
    // [0][0]
    matrix[3 * 0 + 0] = 1;
    // [1][1]
    matrix[3 * 1 + 1] = cos(convertDegToRad(angle));
    // [2][2]
    matrix[3 * 2 + 2] = cos(convertDegToRad(angle));
    // [1][2]
    matrix[3 * 1 + 2] = -sin(convertDegToRad(angle));
    // [2][1]
    matrix[3 * 2 + 1] = sin(convertDegToRad(angle));
    
    return matrix;
}

Matrix Cube::getYRotationMatrix(double angle){
    Matrix matrix(3, 3);

}

Matrix Cube::getZRotationMatrix(double angle){
    Matrix matrix(3, 3);

}


void Cube::render(Gdiplus::Graphics& graphics){
    Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
    
    std::vector <Gdiplus::PointF*> faces = calFaces();

    for (int i = 0; i < faces.size(); i++){
        graphics.DrawPolygon(&pen, faces[i], SQUARE_SIDES);
    }

    for (int i = 0; i < faces.size(); i++){
        delete[] faces[i];
    }
}

void Cube::spin(){

}
