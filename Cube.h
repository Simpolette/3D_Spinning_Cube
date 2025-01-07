#ifndef _CUBE_H_
#define _CUBE_H_

#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <vector>
#ifndef CUBE
#define CUBE
#define SQUARE_SIDES 4
#endif

// #pragma comment (lib,"Gdiplus.lib")

class Cube{

private:
    Gdiplus::PointF* points;
    double side;

private:
    std::vector <Gdiplus::PointF*> calFaces();

public:
    Cube();
    Cube(const Gdiplus::PointF& origin);
    ~Cube();
    void render(Gdiplus::Graphics& graphics);
    void spin();
};


#endif