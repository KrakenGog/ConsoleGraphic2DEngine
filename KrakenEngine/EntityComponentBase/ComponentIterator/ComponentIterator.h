#pragma once

#include "EntityComponentBase/Component.h"

template<class T>
class ComponentIterator {
public:
	ComponentIterator() : _end(true){}

	virtual ComponentIterator& operator++() = 0;
 	virtual T& operator*() = 0;
	virtual bool IsEnd() { return _end; }

	bool operator==(ComponentIterator& it);

	bool _end;
};

template<class T>
inline bool ComponentIterator<T>::operator==(ComponentIterator& it)
{
	return _end && it._end;
}
