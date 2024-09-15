#pragma once

#include <vector>
#include <stdexcept>
#include "Math/Vector.h"

template<class T>
class Matrix
{
public:

	Matrix(int rows, int columns);
	template<int Dim>
	Matrix(Vector<T, Dim>& vec, int dimensions = Dim);
	Matrix(const Matrix<T>& other);

	T& Get(int i, int j);
	const T& Get(int i, int j) const;
	template<int Dim>
	Vector<T, Dim> ToVector();

	
	Matrix<T> operator*(const Matrix<T>& other) const;
	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator*=(T scalar);

	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator*(T scalar) const;
	
	template<int Dimensions>
	Vector<T, Dimensions> operator*(Vector<T, Dimensions>& vec);

	
	
	T Det() const;

	
	Matrix<T> GetSubMatrix(int row, int column) const;


private:
	int _columns, _rows;

	std::vector<T> _data;
};

template<class T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	Matrix<T> result(_rows, other._columns);

	for (size_t t = 0; t < _columns; t++)
	{
		for (size_t i = 0; i < _rows; i++)
		{
			for (size_t j = 0; j < other._columns; j++)
			{
				result._data[i * other._columns + j] +=_data[i * _columns + t] * other._data[other._columns * t + j];
				
			}
		}
	}

	return result;
}



template<class T>
inline Matrix<T>::Matrix(int rows, int columns)
{
	_rows = rows;
	_columns = columns;

	_data.resize(_rows * _columns, 0);
}

template<class T>
inline Matrix<T>::Matrix(const Matrix<T>& other) : _data(other._data)
{
	_rows = other._rows;
	_columns = other._columns;
}

template<class T>
inline T& Matrix<T>::Get(int i, int j)
{
	if (i < 0 || i >= _rows || j < 0 || j >= _columns)
		throw std::invalid_argument("Arguments goes out of range");

	return _data[i * _columns + j];
}

template<class T>
inline const T& Matrix<T>::Get(int i, int j) const
{
	if (i < 0 || i >= _rows || j < 0 || j >= _columns)
		throw std::invalid_argument("Arguments goes out of range");

	return _data[i * _rows + j];
}



template<class T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			Get(i, j) += other.Get(i, j);
		}
	}
	
}

template<class T>
inline Matrix<T>& Matrix<T>::operator*=(T scalar)
{
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			Get(i, j) *= scalar;
		}
	}

	return *this;
}

template<class T>
inline Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	return  Matrix<T>((*this)) += other;
}

template<class T>
inline Matrix<T> Matrix<T>::operator*(T scalar) const
{
	return Matrix<T>((*this)) *= scalar;
}




template<class T>
inline T Matrix<T>::Det() const
{
	if(_rows != _columns)
		throw std::exception("Matrix need to have Rows = Columns");
	int size = _rows;
	int currentColumn = 0;
	int sign = 1;
	int det = 0;


	if (size == 2) {
		return Get(0, 0) * Get(1, 1) - Get(1, 0) * Get(0, 1);
	}
	else {
		while (currentColumn < _columns) {
			det += Get(0, currentColumn) * sign * GetSubMatrix(0, currentColumn).Det();
			sign *= -1;
			++currentColumn;
		}
	}

	return det;
}



template<class T>
Matrix<T> Matrix<T>::GetSubMatrix(int row, int column) const
{
	Matrix<T> result(_rows - 1, _columns - 1);
	int k = 0;
	int t = 0;

	for (size_t i = 0; i < _rows; i++)
	{
		if (i == row) 
			continue;
		
		t = 0;

		for (size_t j = 0; j < _columns; j++)
		{
			if (j == column)
				continue;

			result.Get(k, t) = Get(i, j);

			++t;
		}

		++k;
	}

	return result;
}

template<class T>
template<int Dim>
inline Matrix<T>::Matrix(Vector<T, Dim>& vec, int dimensions)
{
	_rows = dimensions;
	_columns = 1;

	_data.resize(_rows * _columns, 0);

	for (size_t i = 0; i < dimensions; i++)
	{
		if (i >= Dim)
		{
			_data[i] = 1;
			continue;
		}
		_data[i] = vec[i];
	}
}

template<class T>
template<int Dim>
inline Vector<T, Dim> Matrix<T>::ToVector()
{
	if (_columns != 1 || _rows < Dim)
		throw std::exception("Cant do conversion");

	Vector<T, Dim> result;

	for (size_t i = 0; i < Dim; i++)
	{
		result[i] = Get(i, 0);
	}

	return result;
}


template<class T>
template<int Dimensions>
inline Vector<T, Dimensions> Matrix<T>::operator*(Vector<T, Dimensions>& vec)
{
	if (Dimensions > _columns)
		throw std::exception("Vector cant be bigger then matrix");

	Matrix<T> m(vec, _columns);

	

	return (*this * m).ToVector<Dimensions>();
}
