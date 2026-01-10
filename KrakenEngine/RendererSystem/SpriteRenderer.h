#pragma once

#include "SpriteSystem/Sprite.h"
#include "RenderField.h"
#include "EntityComponentBase/ComponentIterator/ComponentIterator.h"
#include <vector>
#include "Components/SpriteRenderData.h"
#include <iostream>
#include <algorithm>
#include "Components/Transform.h"
#include "Camera.h"



class SpriteRenderer {
public:
	void Render(ComPtr<SpriteRenderData> data, RenderField& field, ComPtr<Camera> camera);
};