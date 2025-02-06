#include "RenderField.h"

RenderField::RenderField(int width, int height)
{
	Init(width, height);
}

void RenderField::Init(int width, int height)
{
	_data.resize(_maxHeight * _maxWidth);
	std::fill(_data.begin(), _data.end(), CHAR_INFO());
	_depthMap.resize(_maxHeight * _maxWidth);
	std::fill(_depthMap.begin(), _depthMap.end(), INT_MIN);

	Resize(width, height);
}

void RenderField::Resize(int width, int height)
{
	_width = width;
	_height = height;
}

void RenderField::Clear()
{

	std::fill(_data.begin(), _data.begin() + _width * _height, CHAR_INFO());
	std::fill(_depthMap.begin(), _depthMap.begin() + _width * _height, INT_MIN);

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
	if ((x >= 0 && x < _width) && (y >= 0 && y < _height))
	{
		_data[_width * y + x].Char.UnicodeChar = c;
		_data[_width * y + x].Attributes = attributes;
	}
}

void RenderField::SetDepthAt(int x, int y, int depth)
{
	if ((x >= 0 && x < _width) && ( y >= 0 && y < _height))
	{
		_depthMap[_width * y + x] = depth;
	}
}

void RenderField::SetDepthAtIfGreater(int x, int y, int depth)
{
	if (depth > _depthMap[_width * y + x]) {
		SetDepthAt(x, y, depth);
	}
}

bool RenderField::IsGreaterDepthAt(int x, int y, int depth)
{
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return false;

	return depth > _depthMap[_width * y + x];
}
