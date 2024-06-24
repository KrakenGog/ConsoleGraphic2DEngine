#pragma once
#include <math.h>
class Point
{
public:
    int x;
    int y;

    Point() : x(),y() {};
    Point(int x, int y);

    float GetMagnitude();

    Point operator+(const Point& point) {
        return { x + point.x, y + point.y };
    }

    Point operator-(const Point& point) {
        return { x - point.x, y - point.y };
    }

    Point operator/(int number) {
        return {int(float(x) / number),int(float(y) / number)};
    }
};

