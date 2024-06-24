#include "Entity.h"

void Entity::AddComponent(Component* component)
{
	_components.push_back(component);
}
