#pragma once
#include "Math/Matrix.h"
#include "EntityComponentBase/Component.h"

class Transform : public Component {

    //COMPONENT(10)
public:
    Vector2 Position = Vector2(0,0);
    double Rotation = 0;
    Vector2 Scale = Vector2(1,1);

    Matrix<double> GetTransformationMatrix();
    void SetPosition(double x, double y);
};

