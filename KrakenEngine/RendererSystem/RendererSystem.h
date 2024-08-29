#pragma once

#include "EntityContainers/EntityContainer.h"
#include "Components/SpriteRenderData.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Utils/Console.h"

class RendererSystem {
public:
	void Render(EntityContainer& container, RenderField& field);

private:
	SpriteRenderer _spriteRenderer;
};