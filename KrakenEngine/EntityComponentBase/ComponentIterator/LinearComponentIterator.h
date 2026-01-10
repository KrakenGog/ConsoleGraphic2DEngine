#include "ComponentIterator.h"
#include "EntityComponentBase/ComponentAllocator.h"
#include <vector>

template<class T>
class LinearComponentIterator : public ComponentIterator<T> {
public:

	LinearComponentIterator() : ComponentIterator<T>() {}
	
	template<class ... Args>
	LinearComponentIterator(Args... data) {
		(_dataList.push_back(data),...);
		this->_end = false;
	}

	void AddLine(LinearAllocatedData* line) {
		_dataList.push_back(line);
		this->_end = false;
	}
	
	ComponentIterator<T>& operator++() override;
		
		
	

	ComPtr<T> operator*() override {
		if (this->_end)
			throw std::exception("Iterator has not been inited or out of range");

		return ComPtr<T>(reinterpret_cast<T**>(_dataList[_currentLine]->Pointers[_current]));
		//return *reinterpret_cast<T*>(_dataList[_currentLine]->Memory + _dataList[_currentLine]->CellSize * _current);
	}

private:
	 
	
	int _current = 0;
	int _currentLine = 0;
	std::vector<LinearAllocatedData*> _dataList;
};

template<class T>
inline ComponentIterator<T>& LinearComponentIterator<T>::operator++()
{
	for (int x = _currentLine; x < _dataList.size(); x++)
	{
		
		for (int i = _current + 1; i < _dataList[x]->CellCount; i++)
		{
			if (_dataList[x]->CellStates[i]) {
				_current = i;
				_currentLine = x;
				return *this;
			}
		}
		_current = -1;
	}
	this->_end = true;
	return *this;
}
