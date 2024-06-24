#include "UIContainer.h"

void UIContainer::UpdateLogic()
{
	int count = childs.size();
	if (count < 2)
		return;
	int index = 0;
	int sizeOfContainer = rect.right / count - 1;

	for (auto element : childs) {
		Rect newRect(rect.left + sizeOfContainer * index, sizeOfContainer * (index + 1), rect.top, rect.buttom);
		element->updateRect = false;
		element->RescaleByRect(newRect);
		++index;
	}

}
