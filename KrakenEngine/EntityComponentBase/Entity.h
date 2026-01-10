#pragma once
#include <list>

#include "EventSystem/Event.h"
#include <iostream>
#include <string>
#include "EntityComponentBase/DoublePointer.h"


class Component;
class Transform;

class Entity
{
public:
	
	Entity();
	Entity(ComPtr<Transform> transform);
	

	
	ComPtr<Component> AddComponent(ComPtr<Component> component);
	template<class ... Components>
	Entity* AddComponents(Components... component);
	void Update() {}
	void SetTransform(ComPtr<Transform> transform);
	Transform& GetTransform();
	std::list<ComPtr<Component>>& GetComponents();

	template<class T>
	std::list<ComPtr<T>> FindComponentsOfType();

	template<class T>
	ComPtr<T> FindComponentOfType();

	template<class T>
	std::list<ComPtr<T>> FindComponentsInParent(bool includeCurrent = true);


	template<class T>
	ComPtr<T> FindComponentInParent(bool includeCurrent = true);

	template<typename T>
	ComPtr<T> GetComponentOfType();

	Entity* GetParent() { return _parent; }


private:
	std::list<ComPtr<Component>> _components;
	ComPtr<Transform> _transform;
	Entity* _parent = nullptr;
};

template<class ...Components>
inline Entity* Entity::AddComponents(Components ...component)
{
	(AddComponent(component), ...);
	(component->Inject(), ...);

	return this;
}

template<class T>
inline std::list<ComPtr<T>> Entity::FindComponentsOfType()
{
	std::list<ComPtr<T>> res;

	for (auto com : _components) {
		if (typeid(*com) == typeid(T)) {
			res.push_back(ComPtr<T>(com));
		}
	}

	return res;
}

template<class T>
inline ComPtr<T> Entity::FindComponentOfType()
{
	return FindComponentsOfType<T>().front();
}

template<class T>
inline std::list<ComPtr<T>> Entity::FindComponentsInParent(bool includeCurrent)
{
	std::list<ComPtr<T>> res;
	Entity* current = this;

	if (includeCurrent)
		res = FindComponentsOfType<T>();
	

	current = current->_parent;

	while (current) {
		auto coms = current->FindComponentsOfType<T>();
		res.push_back(coms);

		current = current->_parent;
	}

	return res;
}

template<class T>
inline ComPtr<T> Entity::FindComponentInParent(bool includeCurrent)
{
	ComPtr<T> res = nullptr;
	Entity* current = this;

	if (includeCurrent) 
		res = current->FindComponentOfType<T>();
	
	current = current->_parent;

	while (res == nullptr && current != nullptr) {
		res = current->FindComponentOfType<T>();

		current = current->_parent;
	}

	return res;
}

template<typename T>
inline ComPtr<T> Entity::GetComponentOfType()
{
	auto res = FindComponentOfType<T>();

	if (res == nullptr)
	{
		std::string msg = "Cant find component with type ";
		msg.append(typeid(T).name());
		throw std::invalid_argument(msg);
	}

	return res;
}
