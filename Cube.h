#ifndef _CUBE_H_
#define _CUBE_H_

#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <vector>

#include "Point3D.h"

#ifndef CUBE
#define CUBE
#define SQUARE_SIDES 4
#define SIDE_LENGTH 100
#endif

// #pragma comment (lib,"Gdiplus.lib")

class Cube{

private:
    Gdiplus::PointF origin;
    Point3D* points;
    double focal;

private:
    std::vector <Gdiplus::PointF*> calFaces();
    // Point3D convert2Dto3D(const Gdiplus::PointF& point2D);

public:
    Cube();
    Cube(const Gdiplus::PointF& origin);
    ~Cube();
    void render(Gdiplus::Graphics& graphics);
    void spin();
};


#endif