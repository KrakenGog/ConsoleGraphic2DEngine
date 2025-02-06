#include "PlayerContoroller.h"


void PlayerContoroller::Inject()
{
	_mover = _owner->GetComponent<UnitMover>();
}

void PlayerContoroller::Update(double delta)
{
	Vector2 dir;

	if (Input::IsPressed(VK_UP))
		dir.Y() = 1;
	if (Input::IsPressed(VK_DOWN))
		dir.Y() = -1;
	if (Input::IsPressed(VK_RIGHT))
		dir.X() = 1;
	if (Input::IsPressed(VK_LEFT))
		dir.X() = -1;

	_mover->Move(dir, delta);
}
