#include "Rect.h"

Rect::Rect() : left(), right(), top(),  buttom()
{
}

Rect::Rect(int left, int right, int top, int buttom)
{
	this->left = left;
	this->right = right;
	this->top = top;
	this->buttom = buttom;
}

Point Rect::GetCenter()
{
	return Point((right + left) / 2,(top + buttom) / 2);
}

void Rect::operator+=(const Point& point)
{
	left += point.x;
	right += point.x;
	top += point.y;
	buttom += point.y;
}
