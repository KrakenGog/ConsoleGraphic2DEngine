#pragma once
#include <list>

#include "EventSystem/Event.h"
#include <iostream>
#include <string>
#include "EntityComponentBase/ComponentPointer.h"



class Component;
class Transform;

class Entity
{
public:
	
	Entity();
	Entity(ComPtr<Transform> transform);
	

	
	ComPtr<Component> AddComponent(ComPtr<Component> component);
	void Update() {}
	void SetTransform(ComPtr<Transform> transform);
	Transform& GetTransform();
	std::list<ComPtr<Component>>& GetComponents();

	template<typename T>
	ComPtr<T> GetComponent() {

		for (auto com : _components) {
			if (typeid(*com) == typeid(T)) {
				return ComPtr<T>(com);
			}
		}
		std::string msg = "Cant find component with type ";
		msg.append(typeid(T).name());
		throw std::invalid_argument(msg);
	}

	Entity* GetParent() { return _parent; }


private:
	std::list<ComPtr<Component>> _components;
	ComPtr<Transform> _transform;
	Entity* _parent = nullptr;
};


