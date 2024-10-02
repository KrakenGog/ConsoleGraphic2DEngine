#pragma once
#include "Entity.h"


#define COMPONENT(count) public: const static int AllocateCount = count;

class Entity;

class Component
{
public:

	const static int AllocateCount = 10;

	Component();
	Component(Entity* owner);

	virtual void FindDependencies() {};

	void SetOwner(Entity* owner);
	Entity& GetOwner() { return *_owner; }
	bool HasOwner() { return _owner != nullptr; }

	virtual void Update() {};

protected:
	Entity* _owner;
};
