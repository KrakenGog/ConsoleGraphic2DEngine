template<class T>
class DoublePointer {
public:
	DoublePointer() : _data(nullptr){}
	DoublePointer(T** data);

	template<class U>
	operator DoublePointer<U>() const;

	T& operator*();
	T* operator->();

	T** GetData();
private:
	T** _data;
};



template<class T>
inline DoublePointer<T>::DoublePointer(T** data)
{
	_data = data;
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

