#include "RenderField.h"

RenderField::RenderField(int width, int height)
{
	Init(width, height);
}

void RenderField::Init(int width, int height)
{
	Resize(width, height);
}

void RenderField::Resize(int width, int height)
{
	if(_data != nullptr)
		delete[] _data;

	_width = width;
	_height = height;

	_data = new CHAR_INFO[GetFullSize()];
	std::fill_n(_data, _width * _height, CHAR_INFO());
}

int RenderField::GetWidth()
{
	return _width;
}

int RenderField::GetHeight()
{
	return _height;
}

int RenderField::GetFullSize()
{
	return _width * _height;
}

void RenderField::SetAt(int x, int y, char c, WORD attributes)
{
	if (x >= 0 && x < _width || y >= 0 && y < _height)
	{
		_data[_width * y + x].Char.UnicodeChar = c;
		_data[_width * y + x].Attributes = attributes;
	}
}
