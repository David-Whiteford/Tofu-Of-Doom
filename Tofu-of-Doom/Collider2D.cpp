#include "Collider2D.h"
#include <iostream>

Collider2D::Collider2D()
{
}

Collider2D::~Collider2D()
{
}

///<summary> Checks collisions of 2D objects by checking their bounds (AABB)</summary>
bool Collider2D::isColliding(Bounds b1, Bounds b2)
{
	// Checks if the edges of each side oppisite overlap (AABB)
	float distX1 = b2.x1 - b1.x2;
	float distX2 = b1.x1 - b2.x2;

	float distY1 = b2.y1 - b1.y2;
	float distY2 = b1.y1 - b2.y2;

	if ((distX1 > 0.0f || distY1 > 0.0f)) 
	{
		std::cout << "false 1" << std::endl;
		return false;
	}
	if (distX2 > 0.0f || distY2 > 0.0f)
	{
		std::cout << "false 2" << std::endl;
		return false;
	}

	std::cout << "colliding" << std::endl;
	return true;
}

void Collider2D::updateBounds(float xPos, float yPos)
{

}
