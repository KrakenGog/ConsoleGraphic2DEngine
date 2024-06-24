#include "UIElement.h"

UIElement::UIElement() 
{
	
}

UIElement::UIElement(Rect rect, Attractions attractions)
{
	this->rect = rect;
	this->attractions = attractions;
}

UIElement::UIElement(Rect rect, Attractions attractions, std::list<UIElement*> childs, UIElement* parent)
{
	this->rect = rect;
	this->attractions = attractions;
	this->childs = childs;
	this->parent = parent;
}

UIElement::~UIElement()
{
//	delete &rect;
//	delete &childs;
//	delete &parent;
//	delete& attractions;
}

void UIElement::AddChild(UIElement* child)
{
	childs.push_back(child);
	child->parent = this;
}

void UIElement::SetParent(UIElement* parent)
{
	this->parent = parent;
	parent->AddChild(this);
}

void UIElement::RescaleByRect(Rect rect)
{
	bool down = (int)attractions & (int)Attractions::Down;
	bool up = (int)attractions & (int)Attractions::Up;
	bool left = (int)attractions & (int)Attractions::Left;
	bool right = (int)attractions & (int)Attractions::Right;
	bool center = (int)attractions & (int)Attractions::Center;

	if (center) {
		Point offset = rect.GetCenter() - this->rect.GetCenter();
		this->rect += offset;

		return;
	}
	if (left && right) {
		this->rect.left = rect.left;
		this->rect.right = rect.right;
	}
	else if (left) {
		int offset = this->rect.left - rect.left;
		this->rect.left = rect.left;
		this->rect.right -= offset;
	}
	else if (right) {
		int offset = this->rect.right - rect.right;
		this->rect.right = rect.right;
		this->rect.left -= offset;
	}

	if (up && down) {
		this->rect.top = rect.top;
		this->rect.buttom = rect.buttom;
	}
	else if (up) {
		int offset = this->rect.top - rect.top;
		this->rect.top = rect.top;
		this->rect.buttom -= offset;
	}
	else if (down) {
		int offset = this->rect.buttom - rect.buttom;
		this->rect.buttom = rect.buttom;
		this->rect.top -= offset;
	}
}

void UIElement::RescaleByParent()
{
	RescaleByRect(parent->rect);
}

Point UIElement::GetPosition()
{
	return rect.GetCenter();
}

void UIElement::AddPosition(Point pos)
{
	rect += pos;
}
