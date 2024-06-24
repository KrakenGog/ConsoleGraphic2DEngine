#pragma once
#include "Rect.h"
#include "UIElement.h"
#include <list>
#include "Attractions.h"

class UIContainer : public UIElement
{
public:
	UIContainer(Rect rect) : UIElement(rect,Attractions::Null){}

	virtual void UpdateLogic() override;
};

