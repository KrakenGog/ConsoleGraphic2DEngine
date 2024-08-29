#pragma once
#include "Utils/Console.h"

class UIUtilites
{
public:
    static Point GetMousePosition();

    static Point ConvertFromScreenToLocal(const Point& point);
    static Point GetLocalMousePosition();
};

