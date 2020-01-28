#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::setPublicTransformToCentre(std::vector<glm::vec3> vertices)
{

	float largestX = vertices[0].x;
	float smallestX = vertices[1].x;

	float largestY = vertices[0].y;
	float smallestY = vertices[1].y;

	float largestZ = vertices[0].z;
	float smallestZ = vertices[1].z;

	for (int i = 0; i < vertices.size(); i++)
	{
		// X
		if (vertices[i].x < smallestX)
		{
			smallestX = vertices[i].x;
		}
		else if (vertices[i].x > largestX)
		{
			largestX = vertices[i].x;
		}

		// Y
		if (vertices[i].y < smallestY)
		{
			smallestY = vertices[i].y;
		}
		else if (vertices[i].y > largestY)
		{
			largestY = vertices[i].y;
		}

		// Z
		if (vertices[i].z < smallestZ)
		{
			smallestZ = vertices[i].z;
		}
		else if (vertices[i].z > largestZ)
		{
			largestZ = vertices[i].z;
		}
	}



	std::cout << "Smallest X: " << smallestX << " Largest X: " << largestX << std::endl;
	std::cout << "Smallest Y: " << smallestY << " Largest Y: " << largestY << std::endl;
	std::cout << "Smallest Z: " << smallestZ << " Largest Z: " << largestZ << std::endl;

	position.x = (smallestX + largestX) / 2;
	position.y = (smallestY + largestY) / 2;
	position.z = (smallestZ + largestZ) / 2;


}

float Transform::distance(sf::Vector2f pos_1, sf::Vector2f pos_2)
{
	float x = pos_2.x - pos_1.x;
	float y = pos_2.y - pos_1.y;
	

	return std::sqrt(((x * x) + (y * y)));

}

float Transform::dotProduct(Position& pos_1, Position& pos_2)
{
	float x = pos_2.x * pos_1.x;
	float y = pos_2.y * pos_1.y;
	float z = pos_2.z * pos_1.z;

	return x + y + z;
}

//float Transform::angleBetween(Position& pos_1, Position& pos_2)
//{
//	return std::acos(dotProduct(pos_1, pos_2) / distance(pos_1, pos_2));
//}

sf::Vector2f Transform::moveTowards(sf::Vector2f t_position, sf::Vector2f t_targetPosition , float maxDistance)
{
	
	float toVecX = t_targetPosition.x - t_position.x;
	float toVecY = t_targetPosition.y - t_position.y;

	float squaredDistance = toVecX * toVecX + toVecY * toVecY;

	if (squaredDistance == 0 || maxDistance >= 0
		&& squaredDistance <= maxDistance * maxDistance)
	{
		return t_targetPosition;

	}

	
	float dist = std::sqrt(squaredDistance);
	sf::Vector2f pos;
	pos.x = t_position.x + toVecX / dist * maxDistance;
	pos.y = t_position.y + toVecY / dist * maxDistance;


	return pos;
}

