#include "Cube.h"

Cube::Cube(){
    points = NULL;
    origin = Gdiplus::PointF(0, 0);
    focal = 500;
}

Cube::Cube(const Gdiplus::PointF& origin){
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

double Cube::convertDegToRad(double degree){
    return degree * M_PI / 180;
}

Matrix Cube::getXRotationMatrix(double angle){
    Matrix matrix(3, 3);
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

Matrix Cube::getYRotationMatrix(double angle){
    Matrix matrix(3, 3);

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

Matrix Cube::getZRotationMatrix(double angle){
    Matrix matrix(3, 3);

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

void Cube::setFOV(double angle){
    Matrix rotateX = getXRotationMatrix(convertDegToRad(0));
    Matrix rotateY = getYRotationMatrix(convertDegToRad(0));
    Matrix rotateZ = getZRotationMatrix(convertDegToRad(30));
    Matrix rotate = rotateX * rotateY * rotateZ;

    for (int i = 0; i < SQUARE_SIDES; i++){        
        points[i] = rotate * points[i];
        points[i].print();
        std::cout << "\n";
    }
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

void Cube::spin(double speed){
    Matrix rotateZ = getZRotationMatrix(convertDegToRad(speed));

    for (int i = 0; i < SQUARE_SIDES; i++){
        points[i] = rotateZ * points[i];
    }
}
