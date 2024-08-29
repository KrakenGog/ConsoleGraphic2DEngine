#pragma once
#include "Point.h"
#include <windows.h>
#include <cwchar>
class Console
{
public:
    static Point GetWindowScale();
    static void SetConsoleSizeByFullScreen();
    static void HideCursor();
    static void DisableSelection();
    static COORD GetConsoleBufferSize();
    static void SetFontSize(int size);
};

