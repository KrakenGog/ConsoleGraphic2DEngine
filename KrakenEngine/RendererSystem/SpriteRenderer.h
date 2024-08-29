#pragma once

#include "SpriteSystem/Sprite.h"
#include "RenderField.h"
#include "EntityComponentBase/ComponentIterator/ComponentIterator.h"
#include <vector>
#include "Components/SpriteRenderData.h"
#include "Components/Transform.h"
#include "Camera.h"

class SpriteRenderer {
public:
	void Render(ComponentIterator<SpriteRenderData>& it, RenderField& field, Camera& camera);
};