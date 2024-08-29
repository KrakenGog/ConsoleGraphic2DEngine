template<class T>
class ComponentPointer {
public:
	ComponentPointer() : _data(nullptr){}
	ComponentPointer(T** data);

	template<class U>
	operator ComponentPointer<U>() const;

	T& operator*();
	T* operator->();

	T** GetData();
private:
	T** _data;
};



template<class T>
inline ComponentPointer<T>::ComponentPointer(T** data)
{
	_data = data;
}

template<class T>
template<class U>
inline ComponentPointer<T>::operator ComponentPointer<U>() const
{
	return ComponentPointer<U>(reinterpret_cast<U**>(_data));
}


template<class T>
inline T& ComponentPointer<T>::operator*()
{
	return **_data;
}

template<class T>
inline T* ComponentPointer<T>::operator->()
{
	return *_data;
}

template<class T>
inline T** ComponentPointer<T>::GetData()
{
	return _data;
}



template<class T>
using ComPtr = ComponentPointer<T>;