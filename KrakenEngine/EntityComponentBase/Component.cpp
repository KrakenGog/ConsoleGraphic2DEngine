#include "Component.h"

Component::Component() : _owner(nullptr){}

Component::Component(Entity* owner) : _owner(owner){}

void Component::SetOwner(Entity* owner)
{
	_owner = owner;
}


