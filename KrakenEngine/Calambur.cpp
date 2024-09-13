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
//}

int main()
{
    //Test();
    //system("pause");

    Matrix<double> m(3,3);
    m.Get(0, 0) = 2;
    m.Get(0, 2) = 10;
    m.Get(1, 1) = 2;
    m.Get(1, 2) = 2;
    m.Get(2, 2) = 2;
    m.Get(2, 0) = 10;
    int det = m.Det();

    Matrix<double> m2(m);
    Matrix<double> m3 = m * m2;

    Vector2 vec = {1,2};
    Vector2 f = m * vec;

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
    entity.GetTransform().position.X() = 0;
    entity.GetTransform().position.Y() = 0;

    ComPtr<SpriteRenderData> spriteRenderData = comCreator.Create<SpriteRenderData>();
    
    spriteRenderData->Init(sprite, 0);
    
    entity.AddComponent(spriteRenderData);



    Entity& cameraEn = *creator.Create();
    
    ComPtr<Camera> camera = comCreator.Create<Camera>();
    cameraEn.AddComponent(camera);
    camera->FindDependencies();
    

    RendererSystem renderSystem;

    
    

    DWORD dw = 0;
    float timer = 0;
    
    Console::SetConsoleSizeByFullScreen();
    Console::DisableSelection();
    Console::HideCursor();

    SMALL_RECT writeRegion = { 0, 0, 79, 24 };
    RenderField field;
    //camera->SetZoom(2);
    //field.Resize(100, 100);
    while (true)
    {
        HandleBufferSizeChanged(field);
        camera->SetSize(Vector2(field.GetWidth(), field.GetHeight()));
        
        //screen.Clear();
        field.Clear();

        timer = clock() / 50;
        camera->GetOwner().GetTransform().position.X() = -timer / 10;
       // WriteText(field, { 50,10 }, std::to_string(camera->GetOwner().GetTransform().position.X()));
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
       
        
        //page.Render(screen);
        WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), field.GetData(), {(short)field.GetWidth(), (short)field.GetHeight()}, {0,0}, &writeRegion);
    }

    return 0;
}





