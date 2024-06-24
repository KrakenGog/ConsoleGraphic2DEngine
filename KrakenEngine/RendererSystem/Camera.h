#pragma once
#include "RenderField.h"
#include "Component.h"
#include "Transform.h"

class Camera : Component {
public:
	void FindDependencies() override;
	const Transform* GetTransform() { return _transform; };
private:
	Transform* _transform;
};