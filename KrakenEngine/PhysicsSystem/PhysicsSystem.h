#pragma once

#include "EntityContainers/EntityContainer.h"
#include <unordered_map>
#include "Components/PhysicalBodyData.h"
#include "box2d/box2d.h"
#include "Transform.h"
#include <typeinfo>
#include "PhysicsSystem/PhysicsShapeAdapter.h"
#include "Components/Colliders/Collider.h"

class PhysicsSystem {
public:
	void Init(EntityContainer& container);
	void Step(EntityContainer& container);
	void SetTimeStep(float value);
	void AddNewComponentHandle(ComPtr<Component> component);
	void AddPhysicalObjectForPhysicsComponent(ComPtr<PhysicalBodyData> component);
	void AddCollider(ComPtr<Collider> collider);
	
	~PhysicsSystem();
private:
	float _timeStep = .01666666;
	std::unordered_map<ComPtr<Component>, b2BodyId> _componentTob2Id;
	ComponentContainer* _container;
	b2WorldId _worldId;
	PhysicsShapeAdapter _adapter;
};