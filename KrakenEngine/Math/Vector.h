#pragma once

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <array>


template<class T, int Dimensions>
class Vector {
public:
	Vector();
	Vector(std::initializer_list<T>& list);
	Vector(const Vector<T, Dimensions>& vec);
	
	Vector(T x, T y);
	Vector(T x, T y, T z);

	T& operator[](int i);
	const T& operator[](int i) const;

	Vector<T, 2> GetProjOnVecParralelOther2D(Vector<T, Dimensions> On, Vector<T, Dimensions> Other);

	Vector<T, Dimensions>& operator+=(const Vector<T, Dimensions>& other);
	Vector<T, Dimensions>& operator-=(const Vector<T, Dimensions>& other);
	Vector<T, Dimensions>& operator*=(T scalar);
	Vector<T, Dimensions>& operator/=(T scalar);
	
	Vector<T, Dimensions> operator+(const Vector<T, Dimensions>& other) const;
	Vector<T, Dimensions> operator-(const Vector<T, Dimensions>& other) const;
	Vector<T, Dimensions> operator*(T scalar) const;
	Vector<T, Dimensions> operator/(T scalar) const;
	friend Vector<T, Dimensions> operator*(T scalar, const Vector<T, Dimensions>& vector);
	T operator*(const Vector<T, Dimensions>& vec) const;

	T Length();


	static T Dot(const Vector<T, Dimensions>& left,const Vector<T, Dimensions>& right);
	static Vector<T, Dimensions> Cross(const Vector<T, Dimensions>& left,const Vector<T, Dimensions>& right);

	static Vector<T, Dimensions> One();

	T& X() { return _data[0]; }
	T& Y() { return _data[1]; }
	T& Z() { return _data[2]; }
	T& W() { return _data[3]; }

	const T& Y() const { return _data[1]; }
	const T& X() const { return _data[0]; }
	const T& Z() const { return _data[2]; }
	const T& W() const { return _data[3]; }
	
private:
	std::array<T, Dimensions> _data;
};

template<class T, int Dimensions>
inline Vector<T, Dimensions>::Vector()
{
	for (size_t i = 0; i < Dimensions; i++)
	{
		_data.fill(T());
	}
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>::Vector(std::initializer_list<T>& list)
{
	for (size_t i = 0; i < Dimensions; i++)
	{
		_data[i] = list[i];
	}
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>::Vector(const Vector<T, Dimensions>& vec)
{
	_data = vec._data;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>::Vector(T x, T y)
{
	_data[0] = x;
	_data[1] = y;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>::Vector(T x, T y, T z)
{
	_data[0] = x;
	_data[1] = y;
	_data[2] = z;
}

template<class T, int Dimensions>
inline T& Vector<T, Dimensions>::operator[](int i) 
{
	if (i >= Dimensions || i < 0)
		throw std::invalid_argument("Index is out of demensions");

	return _data[i];
}

template<class T, int Dimensions>
inline const T& Vector<T, Dimensions>::operator[](int i) const
{
	if (i >= Dimensions || i < 0)
		throw std::invalid_argument("Index is out of demensions");

	return _data[i];
}

template<class T, int Dimensions>
inline Vector<T, 2> Vector<T, Dimensions>::GetProjOnVecParralelOther2D(Vector<T, Dimensions> On, Vector<T, Dimensions> Other)
{
	int cross1X = (-Other.X() * X() - Other.Y() * Y()) * On.Y() / (On.X() * Other.Y() - Other.X() * On.Y());
	int cross1Y = -On.X() * cross1X / On.Y();
	return Vector<T, 2>(cross1X, cross1Y);
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>& Vector<T, Dimensions>::operator+=(const Vector<T, Dimensions>& other)
{
	for (size_t i = 0; i < Dimensions; i++)
	{
		(*this)[i] += other[i];
	}

	return *this;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>& Vector<T, Dimensions>::operator-=(const Vector<T, Dimensions>& other)
{
	for (size_t i = 0; i < Dimensions; i++)
	{
		(*this)[i] -= other[i];
	}

	return *this;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>& Vector<T, Dimensions>::operator*=(T scalar)
{
	for (size_t i = 0; i < Dimensions; i++)
	{
		(*this)[i] *= scalar;
	}

	return *this;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions>& Vector<T, Dimensions>::operator/=(T scalar)
{
	for (size_t i = 0; i < Dimensions; i++)
	{
		(*this)[i] /= scalar;
	}

	return *this;
}



template<class T, int Dimensions>
inline Vector<T, Dimensions> Vector<T, Dimensions>::operator+(const Vector<T, Dimensions>& other) const
{
	Vector<T, Dimensions> result(*this);
	
	return result += other;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions> Vector<T, Dimensions>::operator-(const Vector<T, Dimensions>& other) const
{
	Vector<T, Dimensions> result(*this);

	return result -= other;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions> Vector<T, Dimensions>::operator*(T scalar) const
{
	Vector<T, Dimensions> result(*this);
	
	return result *= scalar;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions> Vector<T, Dimensions>::operator/(T scalar) const
{
	Vector<T, Dimensions> result(*this);

	return result /= scalar;
}

template<class T, int Dimensions>
T Vector<T, Dimensions>::operator*(const Vector<T, Dimensions>& vec) const
{
	T result{};
	for (size_t i = 0; i < Dimensions; i++)
	{
		result += (*this)[i] * vec[i];
	}
	return result;
}

template<class T, int Dimensions>
inline T Vector<T, Dimensions>::Length()
{
	T result = 0;
	for (size_t i = 0; i < Dimensions; i++)
	{
		result += _data[i] * _data[i];
	}
	return sqrt(result);
}

template<class T, int Dimensions>
inline T Vector<T, Dimensions>::Dot(const Vector<T, Dimensions>& left,const Vector<T, Dimensions>& right)
{
	return left * right;
}

template<class T, int Dimensions>
inline Vector<T, Dimensions> Vector<T, Dimensions>::Cross(const Vector<T, Dimensions>& left, const Vector<T, Dimensions>& right)
{
	return Vector<T>(left[1] * right[2] - right[1] * left[2], -(left[0] * right[2] - right[0] * left[2], left[0] * right[1] - right[0] * left[1]));
}

template<class T, int Dimensions>
inline Vector<T, Dimensions> Vector<T, Dimensions>::One()
{
	return Vector<T, Dimensions>(1,1);
}

template<class T, int Dimensions>
Vector<T, Dimensions> operator*(T scalar, const Vector<T, Dimensions>& vector) {
	return vector *= scalar;
}

typedef Vector<double, 3> Vector3;
typedef Vector<double, 2> Vector2;
typedef Vector<int, 3> Vector3Int;
typedef Vector<int, 2> Vector2Int;



