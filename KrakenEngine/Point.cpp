#include "Point.h"

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

float Point::GetMagnitude()
{
	return sqrt(pow(x,2) + pow(y,2));
}
