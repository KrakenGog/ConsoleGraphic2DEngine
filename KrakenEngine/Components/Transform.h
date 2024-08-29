#pragma once
#include "Math/Vector.h"
#include "EntityComponentBase/Component.h"

class Transform : public Component {

    //COMPONENT(10)
public:
    Vector2 position;

    void SetPosition(double x, double y);
};

