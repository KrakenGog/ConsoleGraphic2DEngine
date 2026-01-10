#include "MainScene.h"

void MainScene::Update(double delta)
{
	auto it = _container->GetComponents().GetIterator<Component>();
	//_player->GetTransform().Rotation += 5;
	while (!it.IsEnd()) {
		(*it)->Update(delta);
		++it;
	}
}
