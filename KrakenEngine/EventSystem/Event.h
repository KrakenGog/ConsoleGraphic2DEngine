#pragma once
#include <set>
#include <list>
#include <vector>
#include <functional>
#include <stdarg.h>
#include <tuple>
#include "MethodContainer.h"
#include <iostream>
//#include <any>

//class FunctionInfo {
//	void* obj;
//	std::type_info type;
//	std::Type e;
//
//	std::_Get_pointer_type(type) operator *() {
//
//	}
//};

template<class ...TParams>
class Event
{
public:

	
	std::list<std::function<void(TParams...)>> methods;
	std::list<std::function<void(TParams...)>> functions;

	
	template<typename T, typename... U>
	size_t getAddress(std::function<T(U...)> f) {
		typedef T(fnType)(U...);
		fnType** fnPointer = f.template target<fnType*>();
		return (size_t)*fnPointer;
	}

	template<class P>
	void AddMethod(void(P::* method)(TParams...), P* parent) {
		MethodContainer<TParams...> container([parent, method](TParams... params) mutable {
			(*parent.*method)(params...);
			}, parent);
		
		methods.push_back(container);
	}

	void AddFunction(std::function<void(TParams...)> func) {
		functions.push_back(func);
	}

	void RemoveFunction(std::function<void(TParams...)> func) {
		int i = 0;
		for (auto f : functions) {
			if (getAddress(f) == getAddress(func)) {
				functions.erase(std::next(functions.begin(), i));
				return;
			}
			++i;
		}

		throw new std::invalid_argument("Function doesnt exists in list");
	}

	void RemoveMethod(void* methodParent) {
		int i = 0;
		for (auto m : methods) {
			if (m == methodParent) {
				
				methods.erase(std::next(methods.begin(),i));
				return;
			}
			++i;
		}

		throw new std::invalid_argument("Method doesnt exists in list");
	}

	void operator () (TParams ...params) {

		for (auto m : methods) {

			m(params...);
		}

		for (auto f : functions) {
			f(params...);
		}
	}
};

