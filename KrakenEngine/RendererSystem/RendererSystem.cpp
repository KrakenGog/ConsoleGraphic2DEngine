#include "RendererSystem.h"

void RendererSystem::Render(EntityContainer& container, RenderField& field)
{

	ComponentContainer components = container.GetComponents();

	auto cameraIt = components.GetIterator<Camera>();

	if (cameraIt.IsEnd())
		throw std::exception("No camera found");

	Camera& camera = *cameraIt;
	Console::SetFontSize(12 * camera.GetZoom());
	auto iter = components.GetIterator<SpriteRenderData>();

	_spriteRenderer.Render(iter, field, camera);
}
