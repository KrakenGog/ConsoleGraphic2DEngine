#include "PhysicsShapeAdapter.h"



b2Polygon PhysicsShapeAdapter::GetShapeFromRect(ComPtr<RectColliderData> rect, b2ShapeDef& def) const
{
	return b2MakeBox(rect->HalfWidth, rect->HalfHeight);
}
