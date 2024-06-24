#include "Screen.h"

void Screen::RenderRect(Point position, int width, int height, char c, Attractions attraction)
{
    ResetByScreenSize(position, width, height, attraction);
    

    for (size_t i = 0; i < width; i++)
    {
        SetAt(position.x + i, position.y, c);
    }

    for (size_t i = 1; i < height; i++)
    {
        SetAt(position.x, position.y + i, c);
        SetAt(position.x + width - 1, position.y +i, c);
    }

    for (size_t i = 0; i < width; i++)
    {
        SetAt(position.x + i, position.y + height, c);
    }
}

void Screen::RenderRect(int width, int height, Attractions attraction, char c)
{
    RenderRect({ 0,0 }, width, height, c, attraction);
}



void Screen::ResetByScreenSize(Point& point,int& width,int& height, Attractions& attractions)
{
    bool down = (int)attractions & (int)Attractions::Down;
    bool up = (int)attractions & (int)Attractions::Up;
    bool left = (int)attractions & (int)Attractions::Left;
    bool right = (int)attractions & (int)Attractions::Right; 

    if (up && down) {
        point.y = 0;
        height = _height;
    }
    else if (up) {
        point.y = 0;
    }
    else if (down) {
        point.y = _height - height - 1;
    }
    
    if (right && left) {
        point.x = 0;
        width = _width;
    }
    else if (left) {
        point.x = 0;
    }
    else if (right) {
        point.x = _width - width - 1;
    }
    
}

void Screen::ResetUI()
{
    for (auto ch : childs) {
        delete ch;
    }
    childs.clear();
}
