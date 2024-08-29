#include "EntityContainer.h"

void EntityContainer::Add(Entity* entity) {
	_entities.push_back(entity);
}

void EntityContainer::Remove(Entity* entity)
{
	_entities.remove(entity);
}
