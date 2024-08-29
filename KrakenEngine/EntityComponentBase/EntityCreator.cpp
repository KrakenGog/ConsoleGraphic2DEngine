#include "EntityCreator.h"
#include "ComponentCreator.h"
#include "Transform.h"

EntityCreator::EntityCreator(EntityContainer* container, ComponentCreator* creator)
{
	_container = container;
	_creator = creator;
}

Entity* EntityCreator::Create()
{
	auto transform = _creator->Create<Transform>();
	Entity* entity = new Entity(transform);
	_container->Add(entity);

	return entity;
}

void EntityCreator::Delete(Entity* entity)
{
	_container->Remove(entity);

	for (auto com : entity->GetComponents()) {
		_creator->Delete(*com.GetData());
	}

	delete entity;
}
