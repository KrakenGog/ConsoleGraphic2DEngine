#pragma once
#include "Rect.h"
#include <list>
#include <memory>
#include "Attractions.h"
class UIElement 
{
public:
	bool updateRect = true;
	bool updateLogic = true;
	bool isVisible = true;
	Rect rect;
	float zPositon;
	std::list<UIElement*> childs;
	UIElement* parent;
	Attractions attractions;

	UIElement();
	UIElement(Rect rect, Attractions attractions);
	UIElement(Rect rect, Attractions attractions, std::list<UIElement*> childs, UIElement* parent);
	~UIElement();
	virtual void Update() {
		if (updateRect)
			UpdateRect();
		if (updateLogic)
			UpdateLogic();

	}
	virtual void UpdateRect() { RescaleByParent(); }
	virtual void UpdateLogic(){}

	void AddChild(UIElement* child);
	void SetParent(UIElement* parent);

	void RescaleByRect(Rect rect);
	void RescaleByParent();

	virtual Point GetPosition();
	virtual void AddPosition(Point pos);
};

