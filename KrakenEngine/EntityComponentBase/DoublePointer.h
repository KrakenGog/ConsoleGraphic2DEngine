#include <typeinfo>



template<class T>
class DoublePointer {
public:
	DoublePointer() : _data(nullptr){}
	DoublePointer(T** data);

	template<class U>
	operator DoublePointer<U>() const;


	bool operator ==(const DoublePointer& other) const;

	bool operator ==(std::nullptr_t) const;
	bool operator !=(std::nullptr_t) const;
	
	bool IsEqualType(const std::type_info& type) {
		return typeid(**_data) == type;
	}

	T& operator*();
	T* operator->();

	T** GetData();

	
	friend struct std::hash<DoublePointer<T>>;
private:
	T** _data;
};

template <class T>
struct std::hash<DoublePointer<T>>
{
	std::size_t operator()(const DoublePointer<T>& k) const
	{
		using std::size_t;
		using std::hash;
		

		

		return hash<T*>()(*(k._data));
	}
};


template<class T>
inline DoublePointer<T>::DoublePointer(T** data)
{
	_data = data;
}

template<class T>
inline bool DoublePointer<T>::operator==(const DoublePointer& other) const
{
	return *_data == *(other._data);
}

template<class T>
inline bool DoublePointer<T>::operator==(std::nullptr_t) const
{
	return _data == nullptr;
}

template<class T>
inline bool DoublePointer<T>::operator!=(std::nullptr_t) const
{
	return _data != nullptr;
}


template<class T>
inline T& DoublePointer<T>::operator*()
{
	return **_data;
}

template<class T>
inline T* DoublePointer<T>::operator->()
{
	return *_data;
}

template<class T>
inline T** DoublePointer<T>::GetData()
{
	return _data;
}

template<class T>
template<class U>
inline DoublePointer<T>::operator DoublePointer<U>() const
{
	return DoublePointer<U>(reinterpret_cast<U**>(_data));
}


template<class T>
using ComPtr = DoublePointer<T>;

