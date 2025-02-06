#include "MainScene.h"

void MainScene::Update(double delta)
{
	auto it = _container->GetComponents().GetIterator<Component>();

	while (!it.IsEnd()) {
		(*it).Update(delta);
		++it;
	}
}
