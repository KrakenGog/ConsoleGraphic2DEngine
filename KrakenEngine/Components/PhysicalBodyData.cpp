#include "PhysicalBodyData.h"

ComPtr<Component> PhysicalBodyData::Init(BodyType type)
{
	Type = type;

	return _this;
}
