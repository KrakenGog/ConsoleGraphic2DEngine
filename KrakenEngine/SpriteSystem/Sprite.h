#pragma once

#include <vector>
#include <string>
#include "../UISystem/Rect.h"

class Sprite
{
public:

	inline const std::vector<std::string>& GetData() const 
	{
		return _data;
	}
	void SetData(std::vector<std::string>& data) 
	{
		_data = data;
	}



	Rect GetRect() {
		int maxLenght = 0;
		for (const auto& item : _data)
		{
			if (item.size() > maxLenght)
				maxLenght = item.size();
		}
		return Rect(0, maxLenght, 0, _data.size());
	}

	Point GetSize() {
		Rect rect = GetRect();
		return { rect.right, rect.buttom };
	}

	void SetPixelPerUnit(int p) {
		if (p <= 0)
			throw std::exception("Pixel per unit cant be equal or less then zero");

		_pixelPerUnit = p;
	}

	int GetPixelPerUnit() { return _pixelPerUnit; }
	int GetWidth() { return _data[0].length(); }
	int GetHeight() { return _data.size(); }

private:
	std::vector<std::string> _data;
	int _pixelPerUnit = 1;
};

