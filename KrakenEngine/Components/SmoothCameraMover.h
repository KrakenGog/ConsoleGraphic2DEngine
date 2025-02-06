#include "RendererSystem/Camera.h"

class SmoothCameraMover : public Component
{
	void Init(ComPtr<Camera> cam);
	void Update(double delta) override;

private:
	ComPtr<Camera> _camera;
};