#pragma once
#include <iostream>
#include "Sprite.h"
#include "Transform.h"
#include <windows.h>
#include "CardView.h"
#include "UIContainer.h"
#include "UIElement.h"
#include "Attractions.h"
#include "GameObject.h"


class Screen : public UIElement
{
public:

    PCHAR_INFO data;

    Screen(const int& width, const int& height) {
        data = new CHAR_INFO[width * height];
        _width = width;
        _height = height;

        std::fill_n(data, GetFullSize(), CHAR_INFO());

        /* for (size_t i = width+1; i < height * (width+1); i +=(width + 1))
         {
             data[i] = '\n';
         }*/
        rect = Rect(0, width, 0, height);

    }

    const int& GetWidth() {
        return _width;
    }
    const int& GetHeight() {
        return _height;
    }

    void SetAt(const int x, const int y, char c,WORD attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED) {
        if (x < 0 || x > _width - 1 || y < 0 || y > _height - 1)
            return;

        data[y * _width + x].Char.UnicodeChar = c;
        data[y * _width + x].Attributes = attributes;
    }

    int GetFullSize() {
        return _width * _height;
    }

    void ResizeBuffer(int width, int height) {
        delete[] data;
        data = new CHAR_INFO[width * height];
        this->_width = width;
        this->_height = height;

        std::fill_n(data, GetFullSize(), CHAR_INFO());

        rect = Rect(0, width, 0, height);
    }
    void Clear() {
        std::fill_n(data, GetFullSize(), CHAR_INFO());
    }

    void Render(const Sprite& sprite, const Transform& transform) {
        for (size_t i = 0; i < sprite.GetData().size(); i++)
        {
            for (size_t t = 0; t < sprite.GetData()[i].size(); t++)
            {
                SetAt(transform.position.x + t, transform.position.y+ i, sprite.GetData()[i][t]);
            }
        }
    }

    void Render(GameObject& gameObject) {
        
    }

    void Render(CardView& card) {
        for (size_t i = 0; i < card.sprite.GetData().size(); i++)
        {
            for (size_t t = 0; t < card.sprite.GetData()[i].size(); t++)
            {
                SetAt(card.rect.left + t, card.rect.top + i, card.sprite.GetData()[i][t], card.attributes);
            }
        }
    }
    void Render(UIContainer& container) {
        RenderRect({ container.rect.left, container.rect.top }, container.rect.right - container.rect.left, container.rect.buttom - container.rect.top,'#', container.attractions);
    }

    void Render(UIElement* element) {
        if (!element->isVisible)
            return;

        if (CardView* view = dynamic_cast<CardView*>(element)) {
            Render(*view);
        }
        else if (UIContainer* container = dynamic_cast<UIContainer*>(element)) {
            Render(*container);
        }
    }

    virtual void Update() override{}

    void RenderRect(Point position, int width, int height, char c = '*', Attractions attraction = Attractions::Null);
    void RenderRect(int width, int height, Attractions attraction , char c = '*');
    
    void ResetByScreenSize(Point& point,int& width,int& height, Attractions& attractions);

    void ResetUI();
private:
    int _width;
    int _height;

    Transform _transform;
};



