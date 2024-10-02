#pragma once

#include <vector>
#include <stdexcept>
#include "Math/Vector.h"
#include <initializer_list>

template<class T>
class Matrix
{
public:
	Matrix();
	Matrix(int rows, int columns);
	Matrix(int rows, int columns, T mainDiagonal);
	template<int Dim>
	Matrix(const Vector<T, Dim>& vec, int dimensions = Dim);
	Matrix(const Matrix<T>& other);
	Matrix(std::initializer_list<std::vector<T>>& list);

	T& Get(int i, int j);
	const T& Get(int i, int j) const;
	template<int Dim>
	Vector<T, Dim> ToVector();
	template<int Dim>
	Vector<T, Dim> GetVector(int column);
	
	Matrix<T>& Set(std::vector<std::vector<T>> data);

	
	Matrix<T> operator*(const Matrix<T>& other) const;
	Matrix<T>& operator*=(const Matrix<T>& other);
	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator*=(T scalar);

	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator*(T scalar) const;
	
	template<int Dimensions>
	Vector<T, Dimensions> operator*(const Vector<T, Dimensions>& vec) const;

	Matrix<T> Inverse();
	
	
	T Det() const;

	
	Matrix<T> GetSubMatrix(int row, int column) const;
	Matrix<T> Transpose();


//private:
	int _columns, _rows;

	std::vector<T> _data;
};

template<class T>
inline Matrix<T>& Matrix<T>::Set(std::vector<std::vector<T>> data)
{
	if (data.size() != _rows || data[0].size() != _columns)
		throw std::invalid_argument("Vector need to match matrix size");

	for (int i = 0; i < data.size(); ++i) {
		
		for (int j = 0; j < data[i].size(); ++j) {
			if (j >= _columns)
				throw std::invalid_argument("Input data list must have same elements size");

			Get(i, j) = data[i][j];
		}
	}

	return *this;
}

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
				result._data[i * other._columns + j] += _data[i * _columns + t] * other._data[other._columns * t + j];

			}
		}
	}


	//for (size_t i = 0; i < _rows; i++)
	//{
	//	for (size_t j = 0; j < other._columns; j++)
	//	{
	//		for (size_t t = 0; t < _columns; t++)
	//		{
	//			result._data[i * other._columns + j] += _data[i * _columns + t] * other._data[other._columns * t + j];
	//		}
	//	}
	//}


	return result;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
{
	if (_rows != _columns)
		throw std::exception("The matrix must be square");
	*this = *this * other;
	return *this;
}



template<class T>
inline Matrix<T>::Matrix()
{
	_rows = 0;
	_columns = 0;
}

template<class T>
inline Matrix<T>::Matrix(int rows, int columns) 
{
	_rows = rows;
	_columns = columns;

	//_data.resize(_rows * _columns);
	for (size_t i = 0; i < _rows * _columns; i++)
	{
		_data.push_back(0);
	}
}

template<class T>
inline Matrix<T>::Matrix(int rows, int columns, T mainDiagonal) : Matrix(rows, columns)
{
	if (rows != columns)
		throw std::exception("The matrix must be square");

	for (size_t i = 0; i < rows; i++)
	{
		Get(i, i) = mainDiagonal;
	}
}

template<class T>
inline Matrix<T>::Matrix(const Matrix<T>& other) : _data(other._data)
{
	_rows = other._rows;
	_columns = other._columns;
}

template<class T>
inline Matrix<T>::Matrix(std::initializer_list<std::vector<T>>& list)
{
	if(list.size() == 0)
		throw std::invalid_argument("Initializer list cant be empty");

	_rows = list.size();
	_columns = list.begin()->size();
	
	int i = 0;
	int j = 0;

	for (int i = 0; i < list.size(); ++i) {
		
		for (auto j = 0; j < (list.begin() + i)->size(); ++j) {
			if (j >= _columns)
				throw std::invalid_argument("Initializer list must have same elements size");

			_data[i * _columns + j] = (list.begin() + i)[j];
			++j;
		}
		++i;
	}
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
inline Matrix<T> Matrix<T>::Inverse()
{
	Matrix<T> added(_rows, _columns);

	int sign = 1;

	for (size_t i = 0; i < _rows; i++)
	{
		sign = i % 2 == 0 ? 1 : -1;
		for (size_t j = 0; j < _columns; j++)
		{
			added.Get(i, j) = GetSubMatrix(i, j).Det() * sign;

			sign *= -1;
		}
	}

	

	return added.Transpose() * (1 / Det());
}

template<class T>
inline T Matrix<T>::Det() const
{
	if(_rows != _columns)
		throw std::exception("Matrix need to have Rows = Columns");
	int size = _rows;
	int currentColumn = 0;
	int sign = 1;
	T det = 0;

	if (size == 1) {
		return Get(0, 0);
	}


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
inline Matrix<T> Matrix<T>::Transpose()
{
	Matrix<T> result(_columns, _rows);

	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			result.Get(j, i) = Get(i, j);
		}
	}
	return result;
}

template<class T>
template<int Dim>
inline Matrix<T>::Matrix(const Vector<T, Dim>& vec, int dimensions) : Matrix<T>(dimensions,1)
{
	

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
template<int Dim>
inline Vector<T, Dim> Matrix<T>::GetVector(int column)
{
	if (Dim > _rows)
		throw std::exception("Vector cant be longer then column");

	Vector<T, Dim> result;

	for (size_t i = 0; i < Dim; i++)
	{
		result[i] = Get(i, column);
	}

	return result;
}


template<class T>
template<int Dimensions>
inline Vector<T, Dimensions> Matrix<T>::operator*(const Vector<T, Dimensions>& vec) const
{
	if (Dimensions > _columns)
		throw std::exception("Vector cant be bigger then matrix");

	Matrix<T> m(vec, _columns);

	

	return (*this * m).ToVector<Dimensions>();
}
