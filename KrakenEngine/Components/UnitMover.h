#pragma once

#include "EntityComponentBase/Component.h"
#include "Math/Vector.h"
#include "Transform.h"

class UnitMover : public Component
{
public:
	int Speed;
public:
	ComPtr<UnitMover> Init(int speed) { Speed = speed; return _this; };

	void Move(Vector2 dir, double delta);
};