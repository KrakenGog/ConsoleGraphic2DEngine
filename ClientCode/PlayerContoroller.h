#pragma once

#include "EntityComponentBase/Component.h"
#include "UnitMover.h"
#include "Input/Input.h"

class PlayerContoroller : public Component
{
private:
	ComPtr<UnitMover> _mover;
public:
	
	void Inject() override;
	void Update(double delta) override;
};