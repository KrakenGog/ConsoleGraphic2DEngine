#pragma once
#include "UIPage.h"
#include "UIContainer.h"
#include "CardView.h"
#include <list>

class GameUIPage : public UIPage
{
public:
	UIContainer* top;
	UIContainer* down;


	std::list<CardView*> topCards;

	virtual void Create(UIElement* root) override;

	void AddTopCard(CardView* card);
};

