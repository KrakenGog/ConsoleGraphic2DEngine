#pragma once
#include "Point.h"
class Rect
{
public:
	int left;
	int right;
	int top;
	int buttom;

	Rect();
	Rect(int left, int right, int top, int buttom);

	Point GetCenter();

	void operator += (const Point& point);
};

