#include "CardDragger.h"

void CardDragger::Init(Selector<CardView>* selector,UIElement* parent, UIElement* draggingParent, std::list<CardView*> cards)
{
	_selector = selector;
	_parent = parent;
	_draggingParent = draggingParent;
	_cards = cards;

	_selector->StartDragging.AddMethod(&CardDragger::OnStartDrag, this);
	_selector->Dragging.AddMethod(&CardDragger::OnDragging, this);
	_selector->EndDragging.AddMethod(&CardDragger::OnDroped, this);
}

void CardDragger::OnStartDrag(Point point, CardView* card)
{
	card->SetParent(_draggingParent);
}

void CardDragger::OnDragging(Point offset, CardView* card)
{
	card->AddPosition(offset);
}

void CardDragger::OnDroped(Point point, CardView* card)
{
	card->SetParent(_parent);
}
