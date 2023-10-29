#include "../header/Point.h"

Point::Point(double inX, double inY)
{
    mX = inX;
    mY = inY;
}

Point::Point(double inX, double inY, double inZ)
{
    mX = inX;
    mY = inY;
    mZ = inZ;
}

Point::~Point()
{
}

double Point::x()
{
    return mX;
}

double Point::y()
{
    return mY;
}

double Point::z()
{
    return mZ;
}
