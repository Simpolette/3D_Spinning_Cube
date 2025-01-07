#include "Cube.h"

Cube::Cube(){
    points = NULL;
    side = 100;
}

Cube::Cube(const Gdiplus::PointF& origin){
    if (!points){
        delete points;
    }
    points = new Gdiplus::PointF[SQUARE_SIDES];
    side = 100;
    points[0] = origin;
    points[1] = Gdiplus::PointF(origin.X + side, origin.Y);
    points[2] = Gdiplus::PointF(origin.X + side - 40, origin.Y - 40);
    points[3] = Gdiplus::PointF(origin.X - 40, origin.Y - 40);
}

Cube::~Cube(){
    delete points;
}

std::vector <Gdiplus::PointF*> Cube::calFaces(){
    std::vector <Gdiplus::PointF*> faces;
    
    // Top face
    faces.push_back(points);

    // Bottom face
    Gdiplus::PointF* bottomFace = new Gdiplus::PointF[SQUARE_SIDES];
    for (int i = 0; i < SQUARE_SIDES; i++){
        bottomFace[i] = Gdiplus::PointF(points[i].X, points[i].Y + side);
    }

    // Middle faces
    for (int i = 0; i < SQUARE_SIDES; i++){
        Gdiplus::PointF* middleFace = new Gdiplus::PointF[SQUARE_SIDES];
        for (int j = 0; j < SQUARE_SIDES; j++){
            if (j < 2){
                // 2 points on top
                middleFace[j] = points[(j + i) % 4];
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

void Cube::render(Gdiplus::Graphics& graphics){
    Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
    
    std::vector <Gdiplus::PointF*> faces = calFaces();

    for (int i = 0; i < faces.size(); i++){
        graphics.DrawPolygon(&pen, faces[i], SQUARE_SIDES);
    }

    for (int i = 1; i < faces.size(); i++){
        delete[] faces[i];
    }
}

void Cube::spin(){

}
