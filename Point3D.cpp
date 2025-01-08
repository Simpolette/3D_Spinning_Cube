#include "Point3D.h"

Point3D::Point3D() : x(0), y(0), z(0){}

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z){}

Gdiplus::PointF Point3D::to2D(double focal, Gdiplus::PointF origin){
    double x = this->x / this->z * focal + origin.X;
    double y = this->y / this->z * focal + origin.Y;
    return Gdiplus::PointF(x, y);
}