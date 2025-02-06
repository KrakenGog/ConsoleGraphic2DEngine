#include "Scene.h"

Scene::Scene()
{
	_container = new EntityContainer(new ComponentAllocator());
	_componentCreator = new ComponentCreator(&_container->GetComponents());
	_entityCreator = new EntityCreator(_container, _componentCreator);
}

void Scene::Update(double delta)
{
	ComponentContainer& comContainer = _container->GetComponents();
	auto typeList = comContainer.GetAllocatedComponentsTypeInfoList();

	auto it = comContainer.GetIteratorByTypeId(&typeid(Transform));

	for (; !it.IsEnd(); ++it)
	{
		(*it).Update(delta);
	}

	for (size_t i = 0; i < typeList.size(); i++)
	{
		if (typeList[i] != &typeid(Transform)) {
			auto it = comContainer.GetIteratorByTypeId(&typeid(Transform));

			for (; !it.IsEnd(); ++it)
			{
				(*it).Update(delta);
			}
		}
	}
}
