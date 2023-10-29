#pragma once

class Point
{
public:
    Point(double inX, double inY);
    Point(double inX, double inY, double inZ);
    ~Point();

    double x();
    double y();
    double z();

private:
    double mX;
    double mY;
    double mZ;
};