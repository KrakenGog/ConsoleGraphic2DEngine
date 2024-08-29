#pragma once

#include "Component.h"

#include <map>
#include <vector>
#include <string>


struct LinearAllocatedData {
	int CellSize;
	int CellCount;
	char* Memory;
	std::vector<bool> CellStates;
	std::vector<char**> Pointers;

	LinearAllocatedData(int cellSize) : CellStates(), CellSize(cellSize), CellCount(0), Memory(nullptr) {}

	~LinearAllocatedData() {
		delete[] Memory;
		for (size_t i = 0; i < CellCount; i++)
		{
			delete* Pointers[i];
		}
	}
	


	bool Full() {

		for (size_t i = 0; i < CellStates.size(); i++)
		{
			if (!CellStates[i])
				return false;
		}

		return true;
	}

	char* GetClosestEmptyCell() {
		for (size_t i = 0; i < CellStates.size(); i++)
		{
			if (!CellStates[i])
				return (Memory + i * CellSize);
		}

		return nullptr;
	}

	void Resize(int newCount) {
		char* newMem = reinterpret_cast<char*>(operator new(newCount * CellSize));
		
		if (Memory != nullptr)
		{
			memcpy(newMem, Memory, CellSize * CellCount);
			operator delete[](Memory);
		}

		Memory = newMem;

		for (size_t i = 0; i < newCount - CellCount; i++)
		{
			CellStates.push_back(false);
		}

		for (size_t i = 0; i < CellCount; i++)
		{
			*(Pointers[i]) = newMem + i * CellSize;
		}
		
		for (size_t i = 0; i < newCount - CellCount; i++)
		{
			Pointers.push_back(nullptr);
		}

		CellCount = newCount;
	}
};

class ComponentAllocator {
public:
	template<class T>
	T* Allocate();
	
	template<class T, class ... Args>
	ComPtr<T> LinearAllocate(Args... args);

	template<class T>
	T* RandomAllocate();

	template<class T>
	LinearAllocatedData* GetAllocatedData();

	template<class T>
	void Delete(T* component);
	
	~ComponentAllocator();

private:
	std::map<std::string,LinearAllocatedData*> _typeData;
};

template<class T>
inline T* ComponentAllocator::Allocate()
{
	return nullptr;
}

template<class T, class ... Args>
inline ComPtr<T> ComponentAllocator::LinearAllocate(Args... args)
{
	int count = T::AllocateCount;
	if (!_typeData.contains(typeid(T).name())) {
		LinearAllocatedData* data = new LinearAllocatedData(sizeof(T));
		data->Resize(count);

		_typeData[typeid(T).name()] = data;
	}

	LinearAllocatedData& data = *_typeData[typeid(T).name()];
	

	if (data.Full()) {
		data.Resize(data.CellCount * 2);
	}


	T* closestCell = reinterpret_cast<T*>(data.GetClosestEmptyCell());
	int cellIndex = closestCell - reinterpret_cast<T*>(data.Memory);
	data.CellStates[cellIndex] = true;
	T** p = new T * ();
	*p = closestCell;
	data.Pointers[cellIndex] = reinterpret_cast<char**>(p);

	new (closestCell) T(args...);

	return ComPtr<T>(p);
}

template<class T>
inline T* ComponentAllocator::RandomAllocate()
{
	
}

template<class T>
inline LinearAllocatedData* ComponentAllocator::GetAllocatedData()
{
	return _typeData[typeid(T).name()];
}

template<class T>
inline void ComponentAllocator::Delete(T* component)
{
	LinearAllocatedData& data = *_typeData[typeid(T).name()];
	int offset = component - reinterpret_cast<T*>(data.Memory);
	data.CellStates[offset] = false;
	//delete component;
}
