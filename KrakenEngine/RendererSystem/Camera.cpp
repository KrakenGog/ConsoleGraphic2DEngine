#include "Camera.h"

void Camera::Init()
{
	_worldToScreen = Matrix<double>(3, 3);
	_worldToScreenInversed = Matrix<double>(3, 3);
	UpdateWorldToScreenMatrix();
}

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
	Vector2 offset = world - _transform->Position;
	Vector2 n = { offset.X() / _size.X() / 2, - offset.Y() / _size.Y() / 2 };
	
	return n / 2 + Vector2::One() / 2;
}

Vector2 Camera::WorldToScreen(const Vector2& world)
{
	return _worldToScreen * world;
}

Vector2 Camera::ScreenToWorld(const Vector2& screen)
{
	return _worldToScreenInversed * screen;
}

void Camera::UpdateWorldToScreenMatrix()
{
	Matrix<double> res(3, 3, 1);
	res *= _transform->GetTransformationMatrix().Inverse();
	res *= Matrix<double>(3,3).Set({
		{1,0,_size.X() / 2},
		{0,-1,_size.Y() / 2},
		{0,0,1}
		});
	
	_worldToScreen = res;
		

	_worldToScreenInversed = _worldToScreen.Inverse();
}

void Camera::Update()
{
	UpdateWorldToScreenMatrix();
}
