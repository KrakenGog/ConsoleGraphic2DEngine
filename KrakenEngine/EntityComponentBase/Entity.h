#pragma once
#include <list>
#include "Component.h"
#include "Event.h"
#include <iostream>
#include <string>

class Component;

class Entity
{
public:
	Event<Component*> ComponentAdded;

	void AddComponent(Component* component);
	void Update() {};

	template<typename T>
	T* GetComponent() {
		for (auto com : _components) {
			if (typeid(com) == typeid(T)) {
				return dynamic_cast<T*>(com);
			}
		}
		std::string msg = "Cant find component with type ";
		msg.append(typeid(T).name());
		throw std::invalid_argument(msg);
	}
private:
	std::list<Component*> _components;
};
