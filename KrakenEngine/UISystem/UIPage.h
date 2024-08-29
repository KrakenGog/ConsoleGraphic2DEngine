#pragma once
#include "RendererSystem/Screen.h"
#include "UIElement.h"
class UIPage
{
public:
	UIElement* root;

	virtual void Create(UIElement* root){}
	virtual void Update();
	virtual void Render(Screen& screen);

private:
	void UpdateElement(UIElement* element);
	void RenderElement(Screen& screen, UIElement* element);
};

