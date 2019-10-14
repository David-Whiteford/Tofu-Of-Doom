#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

float Transform::distance(Position &pos_1, Position &pos_2)
{
	float x = pos_2.x - pos_1.x;
	float y = pos_2.y - pos_1.y;
	float z = pos_2.z - pos_1.z;

	return std::sqrt(((x * x) + (y * y) + (z * z)));
	
}
