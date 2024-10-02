#pragma once

#include "RenderField.h"
#include "EntityComponentBase/Component.h"
#include "Components/Transform.h"
#include "Point.h"
#include "UISystem/Rect.h"

class Camera : public Component {
public:
	void Init();
	void SetSize(const Vector2& size);
	void FindDependencies() override;
	const ComPtr<Transform> GetTransform() { return _transform; };
	double GetZoom() { return _zoom; }
	void SetZoom(double zoom) { _zoom = zoom; }
	Vector2 WorldToScreenNormalized(const Vector2& world);
	Vector2 WorldToScreen(const Vector2& world);
	Vector2 ScreenToWorld(const Vector2& screen);
	void UpdateWorldToScreenMatrix();
	void Update() override;
private:
	ComPtr<Transform> _transform;
	double _zoom = 1;
	Vector2 _size = {0,0};
	Matrix<double> _worldToScreen;
	Matrix<double> _worldToScreenInversed;
};