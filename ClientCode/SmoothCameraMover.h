#include "RendererSystem/Camera.h"
#include "Components/Transform.h"

class SmoothCameraMover : public Component
{
public:
	ComPtr<SmoothCameraMover> Init(ComPtr<Camera> cam, ComPtr<Transform> target);
	void Update(double delta) override;

private:
	ComPtr<Camera> _camera;
	ComPtr<Transform> _target;
};