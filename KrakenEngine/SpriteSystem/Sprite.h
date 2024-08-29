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

private:
	std::vector<std::string> _data;
};

