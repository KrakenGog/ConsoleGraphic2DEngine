#include "Console.h"

Point Console::GetWindowScale()
{
    HWND consoleWindow = GetConsoleWindow();
    RECT rect;
    GetWindowRect(consoleWindow, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    return { width, height };
}

void Console::SetConsoleSizeByFullScreen()
{
    HWND hWindowConsole = GetConsoleWindow();
    MoveWindow(hWindowConsole, 0, 0, 1920, 1080, TRUE);
}

void Console::HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Console::DisableSelection()
{
    DWORD prev_mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS |
        (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
}

COORD Console::GetConsoleBufferSize()
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdout, &csbi);
    return csbi.dwSize;
}

void Console::SetFontSize(int size)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = size;
    cfi.dwFontSize.Y = size;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Console::SetBufferSize(short x, short y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(console, {x,y});
}
