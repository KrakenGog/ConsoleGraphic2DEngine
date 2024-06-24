#pragma once

#include <iostream>
#include <Windows.h>

class RenderField {
public:
	RenderField() = default;
	RenderField(int width, int height);

	void Init(int width, int height);

	void Resize(int width, int height);

	int GetWidth();
	int GetHeight();

	int GetFullSize();

	void SetAt(int x, int y, char c, WORD attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

private:
	int _width;
	int _height;
	PCHAR_INFO _data;
};