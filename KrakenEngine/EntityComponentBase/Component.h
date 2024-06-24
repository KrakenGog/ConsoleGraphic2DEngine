#pragma once
#include "Entity.h"

class Entity;

class Component
{
public:

	Component();
	Component(Entity* owner);

	virtual void FindDependencies() {};

	void SetOwner(Entity* owner);

	virtual void Update() {};

protected:
	Entity* _owner;
};

