#pragma once
#include "Event.h"
#include "CardView.h"
#include "Selector.h"
#include <list>
class CardDragger
{
public:
	Event<CardView*> CardDropped;

	void Init(Selector<CardView>* selector,UIElement* parent, UIElement* draggingParent, std::list<CardView*> cards);

	void OnStartDrag(Point point, CardView* selectable);
	void OnDragging(Point point, CardView* selectable);
	void OnDroped(Point point, CardView* selectable);

private:
	Selector<CardView>* _selector;
	UIElement* _parent;
	UIElement* _draggingParent;
	std::list<CardView*> _cards;
};

