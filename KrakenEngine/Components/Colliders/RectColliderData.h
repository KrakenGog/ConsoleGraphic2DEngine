#pragma once

#include "EntityComponentBase/Component.h"

class RectColliderData : public Component {
public:
	float HalfWidth;
	float HalfHeight;

	ComPtr<Component> Init(float hWidth, float hHeight);
};