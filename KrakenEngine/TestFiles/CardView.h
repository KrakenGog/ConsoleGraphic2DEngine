#pragma once

#include "../Components/Transform.h"
#include "../SpriteSystem/Sprite.h"
#include "../UISystem/ISelectable.h"
#include <windows.h>
#include "../UISystem/UIElement.h"

class CardView : public UIElement, public ISelectable
{
public:
    Transform transform;
    Sprite sprite;
    WORD attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;

    
    virtual Rect GetRect() override;
    virtual float GetZPosition() override;
    //virtual void OnSelected(Point point) override;
    virtual void OnPointEnter(Point point) override;
    virtual void OnPointExit(Point point) override;
};

