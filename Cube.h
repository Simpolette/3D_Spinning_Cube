#ifndef _CUBE_H_
#define _CUBE_H_

#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <vector>
#include <cmath>

#include "Matrix.h"

#ifndef CUBE
#define CUBE
#define SQUARE_SIDES 4
#define SIDE_LENGTH 100
#endif

// #pragma comment (lib,"Gdiplus.lib")

class Cube{

private:
    Gdiplus::PointF origin;
    Matrix* points;
    double focal;

private:
    std::vector <Gdiplus::PointF*> calFaces();
    // Point3D convert2Dto3D(const Gdiplus::PointF& point2D);
    double convertDegToRad(double degree);
    Matrix getXRotationMatrix(double angle);
    Matrix getYRotationMatrix(double angle);
    Matrix getZRotationMatrix(double angle);

public:
    Cube();
    Cube(const Gdiplus::PointF& origin);
    ~Cube();
    void setFOV(double angle);
    void render(Gdiplus::Graphics& graphics);
    void spin(double speed);
};


#endif