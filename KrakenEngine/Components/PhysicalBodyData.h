#pragma once

#include "EntityComponentBase/Component.h"

enum class BodyType {
	Static,
	Dynamic
};

class PhysicalBodyData : public Component {
	COMPONENT(10);

public:

	ComPtr<Component> Init(BodyType type);

	BodyType Type;
};