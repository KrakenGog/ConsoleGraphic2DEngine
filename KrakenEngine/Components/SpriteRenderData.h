#pragma once

#include "EntityComponentBase/Component.h"
#include "SpriteSystem/Sprite.h"
#include "Math/Vector.h"

class SpriteRenderData : public Component {
	COMPONENT(100)
public:
	SpriteRenderData() : _order(0){}
	SpriteRenderData(const Sprite& sprite, int order) {Init(sprite, order); }

	void Init(const Sprite& sprite, int order);

	void SetSprite(Sprite& sprite) { _sprite = sprite; }
	void SetOrder(int order) { _order = order; }
	void SetCenter(Vector2 center) { _center = center; }

	inline Sprite& GetSprite() { return _sprite; }
	inline int GetOrder() { return _order; }
	inline Vector2 GetCenter() { return _center; }
private:
	Sprite _sprite;
	int _order;
	Vector2 _center;
};