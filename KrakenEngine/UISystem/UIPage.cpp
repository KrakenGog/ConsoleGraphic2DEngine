#include "UIPage.h"

void UIPage::Update()
{
    UpdateElement(root);
}

void UIPage::Render(Screen& screen)
{
    RenderElement(screen, root);
}

void UIPage::UpdateElement(UIElement* element)
{
    element->Update();

    for (auto el : element->childs) {
        UpdateElement(el);
    }
}

void UIPage::RenderElement(Screen& screen, UIElement* element)
{
    screen.Render(element);

    for (auto el : element->childs) {
        RenderElement(screen, el);
    }
}
