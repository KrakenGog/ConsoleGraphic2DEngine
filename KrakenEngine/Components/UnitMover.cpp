#include "UnitMover.h"

void UnitMover::Move(Vector2 dir, double delta)
{
	dir.Normalize();

	_owner->GetTransform().Position += dir * Speed * delta;
}
