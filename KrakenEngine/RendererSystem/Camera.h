#pragma once

#include "RenderField.h"
#include "EntityComponentBase/Component.h"
#include "Components/Transform.h"
#include "Point.h"
#include "UISystem/Rect.h"

class Camera : public Component {
public:
	ComPtr<Camera> Init();
	void Inject() override;

	Vector2& GetSize() { return _size; };
	ComPtr<Camera> SetSize(const Vector2& size);
	double GetZoom() { return _zoom; }
	void SetZoom(double zoom) { _zoom = zoom; }
	bool MatchRenderFieldSize() { return _matchRenderFieldSize; };
	Vector2 WorldToScreenNormalized(const Vector2& world);
	Vector2 WorldToScreen(const Vector2& world);
	Vector2 ScreenToWorld(const Vector2& screen);
	void UpdateWorldToScreenMatrix();
	void Update(double delta) override;
private:
	bool _matchRenderFieldSize = true;
	double _zoom = 1;
	Vector2 _size = {2000,1000};
	Matrix<double> _worldToScreen;
	Matrix<double> _worldToScreenInversed;
};