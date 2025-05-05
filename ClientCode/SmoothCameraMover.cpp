#include "SmoothCameraMover.h"

ComPtr<SmoothCameraMover> SmoothCameraMover::Init(ComPtr<Camera> cam, ComPtr<Transform> target)
{
	_camera = cam;
	_target = target;

	return _this;
}

void SmoothCameraMover::Update(double delta)
{
	Transform& cameraTransform = _camera->GetOwner().GetTransform();
	double x = std::lerp(cameraTransform.Position.X(), _target->Position.X(), .2);
	double y = std::lerp(cameraTransform.Position.Y(), _target->Position.Y(), .2);

	cameraTransform.Position = Vector2(x, y);
}
