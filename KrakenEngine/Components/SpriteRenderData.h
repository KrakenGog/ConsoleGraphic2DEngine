#pragma once

#include "EntityComponentBase/Component.h"
#include "SpriteSystem/Sprite.h"

class SpriteRenderData : public Component {
	//COMPONENT(10)
public:
	SpriteRenderData() : _order(0){}
	SpriteRenderData(Sprite& sprite, int order) {Init(sprite, order); }

	void Init(Sprite& sprite, int order);

	void SetSprite(Sprite& sprite) { _sprite = sprite; }
	void SetOrder(int order) { _order = order; }

	Sprite& GetSprite() { return _sprite; }
	int GetOrder() { return _order; }
private:
	Sprite _sprite;
	int _order;
};