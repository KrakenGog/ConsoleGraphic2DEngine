#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

class RenderField {
public:
	RenderField() {Init(0, 0); }
	RenderField(int width, int height);

	void Init(int width, int height);

	void Resize(int width, int height);

	void Clear();

	int GetWidth();
	int GetHeight();

	int GetFullSize();

	PCHAR_INFO GetData() { return _data.data(); }
	

	void SetAt(int x, int y, char c, WORD attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	void SetDepthAt(int x, int y, int depth);
	void SetDepthAtIfGreater(int x, int y, int depth);
	bool IsGreaterDepthAt(int x, int y, int depth);

private:
	int _width;
	int _height;
	int _maxWidth = 200;
	int _maxHeight = 100;
	std::vector<int> _depthMap;
	std::vector<CHAR_INFO> _data;
};