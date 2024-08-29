#include "Entity.h"
#include "Component.h"
#include "Components/Transform.h"



Entity::Entity() : _components(), _transform(nullptr)
{
	_components.push_back(static_cast<ComPtr<Component>>(_transform));
}

Entity::Entity(ComPtr<Transform> transform)
{
	SetTransform(transform);
}
 
ComPtr<Component> Entity::AddComponent(ComPtr<Component> component)
{
	_components.push_back(component);
	component->SetOwner(this);
	return component;
}

void Entity::SetTransform(ComPtr<Transform> transform)
{
	_transform = transform;

	AddComponent(transform);
}

Transform& Entity::GetTransform()
{
	return *_transform;
}

std::list<ComPtr<Component>>& Entity::GetComponents()
{
	return _components;
}
