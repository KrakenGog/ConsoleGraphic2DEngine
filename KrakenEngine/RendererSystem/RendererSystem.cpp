#include "RendererSystem.h"

void RendererSystem::Render(EntityContainer& container, RenderField& field)
{

	ComponentContainer& components = container.GetComponents();

	auto cameraIt = components.GetIterator<Camera>();

	if (cameraIt.IsEnd())
		throw std::exception("No camera found");

	ComPtr<Camera> camera = *cameraIt;
	Vector2 lastSize = camera->GetSize();
	if (camera->MatchRenderFieldSize())
	{
		double k = ((double)field.GetWidth() / field.GetHeight()) / ((double)lastSize.X() / lastSize.Y());
		if (k > 1) {

			camera->SetSize(Vector2(lastSize.X(), lastSize.Y() / k));
		}
		else {
			camera->SetSize(Vector2(lastSize.X() * k, lastSize.Y()));
		}

		//camera.SetSize(Vector2(lastSize.X(), lastSize.Y() * k));
	}
	
	auto iter = components.GetIterator<SpriteRenderData>();

	for(;!iter.IsEnd(); ++iter)
	{
		if (!(*iter)->HasOwner())
			continue;
		_spriteRenderer.Render(*iter, field, camera);

	}

	camera->SetSize(lastSize);
}
