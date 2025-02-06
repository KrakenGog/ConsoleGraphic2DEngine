#include "ComponentAllocator.h"

LinearAllocatedData* ComponentAllocator::GetAllocatedDataByTypeId(const type_info* info)
{
	return _typeData[info];
}

ComponentAllocator::~ComponentAllocator()
{
	for (auto it = _typeData.begin(); it != _typeData.end(); ++it) {
		delete (*it).second;
	}
}
