#pragma once
#include <functional>

template<class ...TParams>
class MethodContainer
{
public:
	using TMethod = std::function<void(TParams...)>;

 	MethodContainer(TMethod method,void* parent) {
		_parentObject = parent;
		_method = method;
	}

	void operator()(TParams... params) {
		_method(params...);
	}

	bool operator == (void* obj) {
		return _parentObject == obj;
	}

private:
	void* _parentObject;
	TMethod _method;
};




