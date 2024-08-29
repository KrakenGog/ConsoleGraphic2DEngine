#include "ComponentAllocator.h"

ComponentAllocator::~ComponentAllocator()
{
	for (auto it = _typeData.begin(); it != _typeData.end(); ++it) {
		delete (*it).second;
	}
}
