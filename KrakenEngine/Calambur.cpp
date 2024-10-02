#include "Components/Transform.h"
#include "EntityComponentBase/Entity.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <fstream>

#include "EntityComponentBase/EntityCreator.h"
#include "EntityComponentBase/ComponentCreator.h"
#include "RendererSystem/Screen.h"
#include "SpriteSystem/SpriteLoader.h"
#include "TestFiles/CardView.h"
#include "UISystem/Selector.h"
#include "UISystem/GameUIPage.h"
#include "UTIls/Console.h"
#include "UISystem/UIUtilites.h"
#include "EventSystem/Event.h"
#include "TestFiles/CardDragger.h"
#include <time.h>

#include "EntityComponentBase/Component.h"
#include "RendererSystem/RendererSystem.h"

#include "Math/Matrix.h"

#include <chrono>
#include <random>




void OnBufferSizeChanged(const int& width, const int& height, Screen& screen) {
    screen.ResizeBuffer(width, height);
}

void WriteText(RenderField& screen,Point point, std::string s) {
    for (size_t i = 0; i < s.size(); i++)
    {
        screen.SetAt(point.x + i, point.y, s[i]);
    }
}

void HandleBufferSizeChanged(RenderField& field) {
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(console, &info))
        throw "AAAA";


    //int width = info.srWindow.Right - info.srWindow.Left + 1;
    int width = info.dwSize.X;
    int height = info.srWindow.Bottom - info.srWindow.Top + 1;
    info.dwSize.X = width;
    info.dwSize.Y = height;

    if (field.GetWidth() != width || field.GetHeight() != height) {
        field.Resize(width, height);
        SetConsoleScreenBufferSize(console, info.dwSize);
    }
  
    
}

//void HandleBufferSizeChanged(Screen& screen) {
//    CONSOLE_SCREEN_BUFFER_INFO info;
//    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    if (!GetConsoleScreenBufferInfo(console, &info))
//        throw "AAAA"; 
//   
//
//    //int width = info.srWindow.Right - info.srWindow.Left + 1;
//    int width = info.dwSize.X;
//    int height = info.srWindow.Bottom - info.srWindow.Top + 1;
//    info.dwSize.X = width;
//    info.dwSize.Y = height;
//
//    if (screen.GetWidth() != width || screen.GetHeight() != height) {
//        OnBufferSizeChanged(width, height, screen);
//        SetConsoleScreenBufferSize(console, info.dwSize);
//    }
//    HWND consoleWindow = GetConsoleWindow();
//    RECT consoleRect;
//    GetWindowRect(consoleWindow, &consoleRect);
//    WriteText(screen, { 15,23 }, std::to_string(consoleRect.right - consoleRect.left));
//    //WriteText(screen, { 0,1 }, "width: " + std::to_string(info.dwSize.X) + " height: " + std::to_string(info.dwSize.Y));
//}

//class A {
//public:
//    void p(Point point, CardView* card);
//    
//};
//
//void p2(int i) {
//    std::cout << i+2;
//}
//class Test11 {
//public:
//    void f(int o) {
//        std::cout << "Method" + std::to_string(o);
//    }
//};
//
//void f2(int r) {
//    std::cout << "Func" + std::to_string(r);
//}
//void Test() {
//    Event<int> ev;
//    Test11 test;
//    ev.AddMethod(&Test11::f, &test);
//    ev.AddFunction(f2);
//
//    ev(2);
//
//    ev.RemoveMethod(&test);
//    ev(3);
//    ev.RemoveFunction(f2);
//    ev(5);
//
//}template<class T>
inline Matrix<double> CashMul(Matrix<double> th, const Matrix<double>& other)
{
    Matrix<double> result(th._rows, th._columns);

    for (size_t t = 0; t < th._columns; t++)
    {
        for (size_t i = 0; i < th._rows; i++)
        {
            for (size_t j = 0; j < other._columns; j++)
            {
                result._data[i * other._columns + j] += th._data[i * th._columns + t] * other._data[other._columns * t + j];

            }
        }
    }



    return result;
}
inline Matrix<double> NonCashMul(Matrix<double> th, const Matrix<double>& other)
{
    Matrix<double> result(th._rows, th._columns);

   


    for (size_t i = 0; i < th._rows; i++)
    {
        for (size_t j = 0; j < other._columns; j++)
        {
            for (size_t t = 0; t < th._columns; t++)
            {
                result._data[i * other._columns + j] += th._data[i * th._columns + t] * other._data[other._columns * t + j];
            }
        }
    }


    return result;
}
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}

int main()
{
    //Test();
    //system("pause");
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 10);

    Matrix<double> m(500, 500);
    
   /* for (size_t i = 0; i < 500; i++)
    {
        for (size_t j = 0; j < 500; j++)
        {
            m.Get(i, j) = dist6(rng);
        }
    }
    Matrix<double> m2(500,500);
    for (size_t i = 0; i < 500; i++)
    {
        for (size_t j = 0; j < 500; j++)
        {
            m2.Get(i, j) = dist6(rng);
        }
    }*/

    //Matrix<double> m3(m);
    //Matrix<double> m4(m2);

    auto st = std::chrono::system_clock::now();
    //CashMul(m3, m3);
    auto en = std::chrono::system_clock::now();
    //CashMul(m4, m4);
    auto en2 = std::chrono::system_clock::now();
    
    DBOUT("Cash:" << std::chrono::duration_cast<std::chrono::milliseconds>(en - st).count() << "\n");
    DBOUT("Non cash:" << std::chrono::duration_cast<std::chrono::milliseconds>(en2 - en).count() << "\n");

    SpriteLoader loader;
    CardView view;
    Selector<CardView> selector;
    CardDragger dragger;

    //Screen screen(10, 10);
    //dragger.Init(selector,&screen,)
   

    GameUIPage page;
    //page.Create(&screen);

    /*for (size_t i = 0; i < 5; i++)
    {
        CardView* view = new CardView();
        view->sprite = loader.Load("D:/projects/KrakenEngine/KrakenEngine/Resources/Models/Test2.txt");
        view->rect = view->sprite.GetRect();
        view->attractions = Attractions::Center;
        page.AddTopCard(view);
        selector.AddSelectable(view);
    }*/
    ComponentAllocator allocator;
    ComponentContainer componentContainer(&allocator);

    ComponentCreator comCreator(&componentContainer);

    EntityContainer container(&allocator);
    EntityCreator creator(&container, &comCreator);

    Sprite sprite = loader.Load("D:/Projects/KrakenEngine/KrakenEngine/Resources/Models/Test2.txt");
    Entity& entity = *creator.Create();
    entity.GetTransform().Position.X() = 0;
    entity.GetTransform().Position.Y() = 0;
    entity.GetTransform().Scale.X() = 2;

    ComPtr<SpriteRenderData> spriteRenderData = comCreator.Create<SpriteRenderData>();
    
    spriteRenderData->Init(sprite, 0);
    
    //entity.AddComponent(spriteRenderData);
    spriteRenderData->SetCenter({ 11,9});

    Sprite sprite2 = loader.Load("D:/Projects/KrakenEngine/KrakenEngine/Resources/Models/Tree.txt");
     // distribution in range [1, 6]

    
    for (size_t i = 0; i < 100; i++)
    {
        Entity& entity2 = *creator.Create();
        entity2.GetTransform().Position.X() = (static_cast<int>(dist6(rng)) - 3) * 8;
        entity2.GetTransform().Position.Y() = (static_cast<int>(dist6(rng)) - 3) * 8;
        entity2.GetTransform().Scale.X() = 1;

        ComPtr<SpriteRenderData> spriteRenderData2 = comCreator.Create<SpriteRenderData>();

        spriteRenderData2->Init(sprite2, 0);

        entity2.AddComponent(spriteRenderData2);
        spriteRenderData2->SetCenter({ 0,0 });
    }

    Entity& cameraEn = *creator.Create();
    
    ComPtr<Camera> camera = comCreator.Create<Camera>();
    cameraEn.AddComponent(camera);
    camera->FindDependencies();

    camera->Init();
    

    RendererSystem renderSystem;

    
    

    DWORD dw = 0;
    float timer = 0;
    
    Console::SetConsoleSizeByFullScreen();
    Console::DisableSelection();
    Console::HideCursor();
    Console::SetFontSize(9);

    SMALL_RECT writeRegion = { 0, 0, 79, 24 };
    RenderField field;
    //camera->SetZoom(2);
    //field.Resize(100, 100);
    

    /* do some work */

    double lastFrameTime = 0;
    long long frameCount = 1;
    double frameSum = 0;
    
    Console::SetBufferSize(79, 24);
    
   
    while (true)
    {
        auto start = std::chrono::system_clock::now();
        HandleBufferSizeChanged(field);
        camera->SetSize(Vector2(field.GetWidth(), field.GetHeight()));
        camera->Update();
        
        //screen.Clear();
        field.Clear();

        timer += double(10) / 1000;
        //entity.GetTransform().Position = Vector2(50,-20);
        entity.GetTransform().Rotation =timer * 100;
        //view.transform.position.x = timer;
        renderSystem.Render(container, field);

        //screen.RenderRect(0, 12, (Attractions)((int)Attractions::Left | (int)Attractions::Right | (int)Attractions::Up));
        //screen.RenderRect(0, 12, (Attractions)((int)Attractions::Left | (int)Attractions::Right | (int)Attractions::Down));
        //page.Update();
        Point mousePos = UIUtilites::GetLocalMousePosition(); 
        //selector.Update();
        /*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            selector.Select(mousePos);
        }*/
        //WriteText(screen, { 10,20 }, std::to_string(mousePos.x));
        SMALL_RECT writeRegion = { 0, 0, Console::GetConsoleBufferSize().X, Console::GetConsoleBufferSize().Y};
       
        
        WriteText(field, { 2,2 }, "frame time: " + std::to_string(lastFrameTime));
        WriteText(field, { 2,4 }, "Average ft: " + std::to_string(frameSum / frameCount));
        //page.Render(screen);
        WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), field.GetData(), {(short)field.GetWidth(), (short)field.GetHeight()}, {0,0}, &writeRegion);
        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        lastFrameTime = elapsed.count();
        ++frameCount;
        frameSum += elapsed.count();
    }

    return 0;
}





