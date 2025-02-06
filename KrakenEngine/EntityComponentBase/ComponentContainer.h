#pragma once

#include "Component.h"
#include "ComponentAllocator.h"
#include "ComponentIterator/LinearComponentIterator.h"

class ComponentContainer {
public:

	ComponentContainer(ComponentAllocator* allocator) : _allocator(allocator) { _allocatedLines = _allocator->GetConstDataPointer(); }

	template<class T, class ... Args>
	ComPtr<T> AddNewComponent(Args... args);
	

	template<class T>
	void RemoveComponent(T* component);

	template<class T>
	LinearComponentIterator<T> GetIterator();

	LinearComponentIterator<Component> GetIteratorByTypeId(const type_info* info);

	std::vector<const type_info*> GetAllocatedComponentsTypeInfoList();

private:
	ComponentAllocator* _allocator;
	const std::map<const type_info*, LinearAllocatedData*>* _allocatedLines;
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

	return (data == nullptr ? LinearComponentIterator<T>() : LinearComponentIterator<T>(data));
}

template<>
inline LinearComponentIterator<Component> ComponentContainer::GetIterator()
{
	LinearComponentIterator<Component> res;

	auto map = _allocator->GetConstDataPointer();
	auto it = map->cbegin();
	
	for (; it != map->cend(); ++it) {
		auto pair = *it;
		res.AddLine(pair.second);
	}   

	return res;
}
