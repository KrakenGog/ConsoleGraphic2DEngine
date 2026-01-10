#include "RectColliderData.h"

ComPtr<Component> RectColliderData::Init(float hWidth, float hHeight)
{
	HalfHeight = hHeight;
	HalfWidth = hWidth;

	return _this;
}
