#pragma once

#include "box2d/box2d.h"
#include "Components/Colliders/RectColliderData.h"

class PhysicsShapeAdapter {
public:
	b2Polygon GetShapeFromRect(ComPtr<RectColliderData> rect, b2ShapeDef& def) const;
};