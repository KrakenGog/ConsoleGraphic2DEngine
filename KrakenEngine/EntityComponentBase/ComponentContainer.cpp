#include "ComponentContainer.h"

LinearComponentIterator<Component> ComponentContainer::GetIteratorByTypeId(const type_info* info)
{
	return LinearComponentIterator<Component>(_allocator->GetAllocatedDataByTypeId(info));
}

std::vector<const type_info*> ComponentContainer::GetAllocatedComponentsTypeInfoList()
{
	std::vector<const type_info*> res(_allocatedLines->size());
	for (auto pair : *_allocatedLines)
	{
		res.push_back(pair.first);
	}
	return res;
}
