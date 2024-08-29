#include "Camera.h"

void Camera::SetSize(const Vector2& size)
{
	_size = size;
}

void Camera::FindDependencies()
{
	_transform = _owner->GetComponent<Transform>();
}

Vector2 Camera::WorldToScreenNormalized(const Vector2& world)
{
	Vector2 offset = world - _transform->position;
	Vector2 n = { offset.X() / _size.X() / 2, - offset.Y() / _size.Y() / 2 };
	
	return n / 2 + Vector2::One() / 2;
}

Vector2 Camera::WorldToScreen(const Vector2& world)
{
	Vector2 offset = world - _transform->position;
	offset.Y() *= -1;

	return offset + Vector2((_size / 2).X(), (_size / 2).Y());
}
