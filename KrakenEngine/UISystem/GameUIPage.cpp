#include "GameUIPage.h"

void GameUIPage::Create(UIElement* root)
{
	this->root = root;
	top = new UIContainer(Rect(0,0,0,11));
	top->attractions = Attractions((int)Attractions::Left | (int)Attractions::Right | (int)Attractions::Up);
	down = new UIContainer(Rect(0, 0, 0, 11));
	down->attractions = Attractions((int)Attractions::Left | (int)Attractions::Right | (int)Attractions::Down);
	root->AddChild(top);
	root->AddChild(down);

}

void GameUIPage::AddTopCard(CardView* card)
{
	top->AddChild(card);
	topCards.push_back(card);
}
