#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <fstream>
#include "Screen.h"
#include "SpriteLoader.h"
#include "CardView.h"
#include "Selector.h"
#include "UIContainer.h"
#include "GameUIPage.h"
#include "Console.h"
#include "UIUtilites.h"
#include "Event.h"
#include "CardDragger.h"
#include <time.h>
#include "RenderField.h"

void OnBufferSizeChanged(const int& width, const int& height, Screen& screen) {
    screen.ResizeBuffer(width, height);
}

void WriteText(Screen& screen,Point point, std::string s) {
    for (size_t i = 0; i < s.size(); i++)
    {
        screen.SetAt(point.x + i, point.y, s[i]);
    }
}


void HandleBufferSizeChanged(Screen& screen) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(console, &info))
        throw "AAAA"; 
   

    //int width = info.srWindow.Right - info.srWindow.Left + 1;
    int width = info.dwSize.X;
    int height = info.srWindow.Bottom - info.srWindow.Top + 1;
    info.dwSize.X = width;
    info.dwSize.Y = height;

    if (screen.GetWidth() != width || screen.GetHeight() != height) {
        OnBufferSizeChanged(width, height, screen);
        SetConsoleScreenBufferSize(console, info.dwSize);
    }
    HWND consoleWindow = GetConsoleWindow();
    RECT consoleRect;
    GetWindowRect(consoleWindow, &consoleRect);
    WriteText(screen, { 15,23 }, std::to_string(consoleRect.right - consoleRect.left));
    //WriteText(screen, { 0,1 }, "width: " + std::to_string(info.dwSize.X) + " height: " + std::to_string(info.dwSize.Y));
}

class A {
public:
    void p(Point point, CardView* card);
    
};

void p2(int i) {
    std::cout << i+2;
}
class Test11 {
public:
    void f(int o) {
        std::cout << "Method" + std::to_string(o);
    }
};

void f2(int r) {
    std::cout << "Func" + std::to_string(r);
}
void Test() {
    Event<int> ev;
    Test11 test;
    ev.AddMethod(&Test11::f, &test);
    ev.AddFunction(f2);

    ev(2);

    ev.RemoveMethod(&test);
    ev(3);
    ev.RemoveFunction(f2);
    ev(5);

}

int main()
{
    //Test();
    //system("pause");

    

    SpriteLoader loader;
    CardView view;
    Selector<CardView> selector;
    CardDragger dragger;

    Screen screen(10, 10);
    //dragger.Init(selector,&screen,)
   

    GameUIPage page;
    page.Create(&screen);

    for (size_t i = 0; i < 5; i++)
    {
        CardView* view = new CardView();
        view->sprite = loader.Load("D:/projects/KrakenEngine/KrakenEngine/Resources/Models/Test2.txt");
        view->rect = view->sprite.GetRect();
        view->attractions = Attractions::Center;
        page.AddTopCard(view);
        selector.AddSelectable(view);
    }

    

    DWORD dw = 0;
    float timer = 0;
    
    Console::SetConsoleSizeByFullScreen();
    Console::DisableSelection();
    Console::HideCursor();
    SMALL_RECT writeRegion = { 0, 0, 79, 24 };
    while (true)
    {
        HandleBufferSizeChanged(screen);
        
        screen.Clear();

        timer = clock() / 50;
        //view.transform.position.x = timer;

        //screen.RenderRect(0, 12, (Attractions)((int)Attractions::Left | (int)Attractions::Right | (int)Attractions::Up));
        //screen.RenderRect(0, 12, (Attractions)((int)Attractions::Left | (int)Attractions::Right | (int)Attractions::Down));

        page.Update();
        Point mousePos = UIUtilites::GetLocalMousePosition(); 
        //selector.Update();
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            selector.Select(mousePos);
        }
        //WriteText(screen, { 10,20 }, std::to_string(mousePos.x));
        SMALL_RECT writeRegion = { 0, 0, Console::GetConsoleBufferSize().X, Console::GetConsoleBufferSize().Y};
        
        page.Render(screen);
        WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), screen.data, { (short)screen.GetWidth(), (short)screen.GetHeight() }, { 0,0 }, &writeRegion);
    }

    return 0;
}





