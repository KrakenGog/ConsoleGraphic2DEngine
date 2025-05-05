#pragma once
#include "Entity.h"



#define COMPONENT(count) public: const static int AllocateCount = count;

class Entity;

class Component
{
public:

	

	COMPONENT(10)

	Component();
	Component(Entity* owner);

	virtual void Inject() {};

	void SetOwner(Entity* owner);
	Entity& GetOwner() { return *_owner; }
	bool HasOwner() { return _owner != nullptr; }

	void SetSelfPointer(ComPtr<Component> selfPointer);

	virtual void Update(double delta) {};

protected:
	Entity* _owner;
	ComPtr<Component> _this;

public:
	bool RecieveUpdate = true;
};
