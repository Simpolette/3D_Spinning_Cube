#include "Cube.h"

Cube::Cube(){
    pen = new Gdiplus::Pen((Gdiplus::Color(0, 0, 0)));
    points = NULL;
    origin = Gdiplus::PointF(0, 0);
    focal = 500;
}

Cube::Cube(const Gdiplus::PointF& origin){
    pen = new Gdiplus::Pen((Gdiplus::Color(0, 0, 0)));
    this->origin = origin;    
    focal = 500;
    points = new Matrix[SQUARE_SIDES];

    // Initalize the top face of the cube
    points[0] = Matrix(-SIDE_LENGTH / 2, -SIDE_LENGTH / 2, SIDE_LENGTH / 2);
    points[1] = Matrix(-SIDE_LENGTH / 2, SIDE_LENGTH / 2, SIDE_LENGTH / 2);
    points[2] = Matrix(SIDE_LENGTH / 2, SIDE_LENGTH / 2, SIDE_LENGTH / 2);
    points[3] = Matrix(SIDE_LENGTH / 2, -SIDE_LENGTH / 2, SIDE_LENGTH / 2);
}

Cube::~Cube(){
    delete[] points;
    delete pen;
}

std::vector <Gdiplus::PointF*> Cube::calFaces(){
    std::vector <Gdiplus::PointF*> faces;
    
    // Top face
    Gdiplus::PointF* topFace = new Gdiplus::PointF[SQUARE_SIDES];
    for (int i = 0; i < SQUARE_SIDES; i++){
        topFace[i] = points[i].to2D(focal, origin);
    }

    faces.push_back(topFace);

    // Bottom face
    Gdiplus::PointF* bottomFace = new Gdiplus::PointF[SQUARE_SIDES];
    for (int i = 0; i < SQUARE_SIDES; i++){
        bottomFace[i] = Gdiplus::PointF(topFace[i].X, topFace[i].Y + SIDE_LENGTH);
    }

    // Middle faces
    for (int i = 0; i < SQUARE_SIDES; i++){
        Gdiplus::PointF* middleFace = new Gdiplus::PointF[SQUARE_SIDES];
        for (int j = 0; j < SQUARE_SIDES; j++){
            if (j < 2){
                // 2 points on top
                middleFace[j] = topFace[(j + i) % 4];
            }
            else{
                // 2 points at bottom
                middleFace[j] = bottomFace[(j + i - 2) % 4];
            }
        }
        // Swapping 2 points for correct order
        std::swap(middleFace[2], middleFace[3]);
        faces.push_back(middleFace);
    }

    faces.push_back(bottomFace);

    return faces;
}

// Point3D Cube::convert2Dto3D(const Gdiplus::PointF& point2D){

// }

void Cube::setFOV(double angle){
    Matrix rotateX = Matrix::getXRotationMatrix(0);
    Matrix rotateY = Matrix::getYRotationMatrix(0);
    Matrix rotateZ = Matrix::getZRotationMatrix(30);
    Matrix rotate = rotateX * rotateY * rotateZ;

    for (int i = 0; i < SQUARE_SIDES; i++){        
        points[i] = rotate * points[i];
    }
}

void Cube::render(Gdiplus::Graphics& graphics){    
    std::vector <Gdiplus::PointF*> faces = calFaces();

    for (int i = 0; i < faces.size(); i++){
        graphics.DrawPolygon(pen, faces[i], SQUARE_SIDES);
    }

    for (int i = 0; i < faces.size(); i++){
        delete[] faces[i];
    }
}

void Cube::spin(double speed){
    Matrix rotateZ = Matrix::getZRotationMatrix(speed);

    for (int i = 0; i < SQUARE_SIDES; i++){
        points[i] = rotateZ * points[i];
    }
}
