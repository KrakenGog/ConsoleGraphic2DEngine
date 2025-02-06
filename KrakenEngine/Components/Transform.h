#pragma once
#include "Math/Matrix.h"
#include "EntityComponentBase/Component.h"

class Transform : public Component {

    COMPONENT(10)
public:
    Vector2 Position;
    double Rotation;
    Vector2 Scale;

    Transform() : Position(), Rotation(0), Scale(1, 1) {};

    Matrix<double> GetTransformationMatrix();
    void SetPosition(double x, double y);
};

