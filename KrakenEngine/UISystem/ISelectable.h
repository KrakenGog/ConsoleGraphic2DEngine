#pragma once
#include "Rect.h"
class ISelectable
{
public:
	virtual Rect GetRect() = 0;
	virtual float GetZPosition() = 0;
	virtual void OnPointEnter(Point point) {};
	virtual void OnSelected(Point point)  {};
	virtual void OnPointExit(Point point) {};
};

