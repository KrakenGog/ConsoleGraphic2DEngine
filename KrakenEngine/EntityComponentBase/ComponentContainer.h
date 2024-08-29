#pragma once

#include "Component.h"
#include "ComponentAllocator.h"
#include "ComponentIterator/LinearComponentIterator.h"



class ComponentContainer {
public:

	ComponentContainer(ComponentAllocator* allocator) : _allocator(allocator){}

	template<class T, class ... Args>
	ComPtr<T> AddNewComponent(Args... args);
	

	template<class T>
	void RemoveComponent(T* component);

	template<class T>
	LinearComponentIterator<T> GetIterator();

private:
	ComponentAllocator* _allocator;
};

template<class T, class ... Args>
inline ComPtr<T> ComponentContainer::AddNewComponent(Args... args)
{
	return _allocator->LinearAllocate<T>(args...);
}

template<class T>
inline void ComponentContainer::RemoveComponent(T* component)
{
	_allocator->Delete(component);
}

template<class T>
inline LinearComponentIterator<T> ComponentContainer::GetIterator()
{
	LinearAllocatedData* data = _allocator->GetAllocatedData<T>();

	return LinearComponentIterator<T>(data);
}
