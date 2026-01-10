#define CLIENT_MODE

#include <iostream>
#include <string>
#include <vector>
#include <conio.h> 
#include <fstream>
#include <time.h>
#include <chrono>

//#include "sigslot/signal.hpp"
#include "UISystem/UIUtilites.h"
#include "PhysicsSystem/PhysicsSystem.h"
#include "Utils/Console.h"
#include "EventSystem/Event.h"
#include "RendererSystem/RendererSystem.h"
#include "Math/Matrix.h"
#include "Scene/Scene.h"

//static Scene* startScene = new Scene();

#ifdef CLIENT_MODE
extern "C"  Scene* getFirstScene();
#endif // CLIENT_MODE



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
        throw "GetConsoleScreenBufferInfo failed";


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

void start()
{
    RendererSystem renderSystem;
    
    DWORD dw = 0;
    float timer = 0;
    
    Console::SetConsoleSizeByFullScreen();
    Console::DisableSelection();
    Console::HideCursor();
    Console::SetFontSize(5);
    
    RenderField field;
   

    double lastFrameTime = 0;
    long long frameCount = 1;
    double frameSum = 0;
    
    Console::SetBufferSize(0, 0);
   
    int targetFrameTime = 10;
    //sigslot::signal<> slot;
    int sl = 0;

#ifdef CLIENT_MODE
    Scene& scene = *getFirstScene();
#endif // CLIENT_MODE

    PhysicsSystem physicsSystem;
    physicsSystem.Init(scene.GetContainer());
    

    scene.Init();

    while (true)
    {
        std::chrono::milliseconds elapsed;
        
        auto start = std::chrono::system_clock::now();
        HandleBufferSizeChanged(field);
       
        field.Clear();

        timer += double(10) / 1000;

        physicsSystem.Step(scene.GetContainer());
       
        Point mousePos = UIUtilites::GetLocalMousePosition(); 
#ifdef CLIENT_MODE
        scene.Update(double(elapsed.count()) / 1000);
        renderSystem.Render(scene.GetContainer(), field);
#endif // CLIENT_MODE

        
        
        SMALL_RECT writeRegion = { 0, 0, Console::GetConsoleBufferSize().X, Console::GetConsoleBufferSize().Y};
       
        
        WriteText(field, { 2,2 }, "frame time: " + std::to_string(lastFrameTime));
        WriteText(field, { 2,4 }, "Average ft: " + std::to_string(frameSum / frameCount));
        WriteText(field, { 2,6 }, "Sleep time " + std::to_string(sl));
        std::stringstream ss;
        
        //page.Render(screen);
        WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), field.GetData(), {(short)field.GetWidth(), (short)field.GetHeight()}, {0,0}, &writeRegion);
        auto end = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        if (elapsed.count() < targetFrameTime) {
            sl = targetFrameTime - elapsed.count();
            //Sleep(targetFrameTime - elapsed.count());
        }

        end = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        lastFrameTime = elapsed.count();
        ++frameCount;
        frameSum += elapsed.count();
    }
}





int main() {
    start();
}