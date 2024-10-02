#include "Transform.h"

Matrix<double> Transform::GetTransformationMatrix()
{
	Matrix<double> transform(3, 3);
	transform.Set({
		{1,0, Position.X()},
		{0,1, Position.Y()},
		{0,0, 1}
	});
	

	Matrix<double> rotation(3, 3);
	rotation.Set({
		{std::cos(Rotation / 57.295779513), -std::sin(Rotation / 57.295779513), 0},
		{std::sin(Rotation / 57.295779513), std::cos(Rotation / 57.295779513),  0},
		{0,                            0,                             1}
	});

	


	Matrix<double> scale(3, 3, 1);
	scale.Get(0, 0) = Scale.X();
	scale.Get(1, 1) = Scale.Y();

	return  transform * rotation * scale;
}

void Transform::SetPosition(double x, double y)
{
	Position.X() = x;
	Position.Y() = y;
}
