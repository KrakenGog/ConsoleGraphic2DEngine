#pragma once
#include "Point.h"
#include <windows.h>
class Console
{
public:
    static Point GetWindowScale();
    static void SetConsoleSizeByFullScreen();
    static void HideCursor();
    static void DisableSelection();
    static COORD GetConsoleBufferSize();
};

