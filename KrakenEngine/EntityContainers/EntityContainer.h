#pragma once

#include "EntityComponentBase/Entity.h"
#include "EntityComponentBase/Component.h"
#include "EntityComponentBase/ComponentContainer.h"
#include <list>

class EntityContainer {
public:
	EntityContainer(ComponentAllocator* allocator) : _componentContainer(allocator){}
		
	
	ComponentContainer& GetComponents();
	void Add(Entity* entity);
	void Remove(Entity* entity);

private:
	ComponentContainer _componentContainer;
	std::list<Entity*> _entities;
};


inline ComponentContainer& EntityContainer::GetComponents()
{
	return _componentContainer;
}

