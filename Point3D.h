#ifndef _POINT_3D_H_
#define _POINT_3D_H_

#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>

class Point3D{

private:
    double x;
    double y;
    double z;

public:
    Point3D();
    Point3D(double x, double y, double z);
    Gdiplus::PointF to2D(double focal, Gdiplus::PointF origin);

};

#endif