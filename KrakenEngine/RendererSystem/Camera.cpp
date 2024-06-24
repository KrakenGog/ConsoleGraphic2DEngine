#include "Camera.h"

void Camera::FindDependencies()
{
	_transform = _owner->GetComponent<Transform>();
}
