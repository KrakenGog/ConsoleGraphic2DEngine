#include "UIUtilites.h"

Point UIUtilites::GetMousePosition()
{
    POINT p;
    Point result;
    GetCursorPos(&p);
    HWND consoleWindow = GetConsoleWindow();
    RECT consoleRect;
    GetWindowRect(consoleWindow, &consoleRect);
    result.x = p.x - consoleRect.left;
    result.y = p.y - consoleRect.top;

    return { result.x, result.y };
}

Point UIUtilites::ConvertFromScreenToLocal(const Point& point)
{
    Point scale = Console::GetWindowScale();
    COORD bufferScale = Console::GetConsoleBufferSize();
    int column = (float(point.x) / scale.x) * bufferScale.X;
    int row = (float(point.y) / scale.y) * bufferScale.Y;
    return { column, row };
}

Point UIUtilites::GetLocalMousePosition()
{
    return ConvertFromScreenToLocal(GetMousePosition());
}
