#pragma once
#include <SFML/Graphics.hpp>

class Raycast
{
public:
	Raycast();
	~Raycast();
	void setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length);
	bool circleHit(sf::Vector2f t_targetPosition, float t_targetRadius);

	sf::VertexArray drawRay();  

private:

	float m_rayLength = 1000;
	sf::Vector2f m_direction;
	sf::Vector2f m_positon;

	sf::Vertex m_raycastLine[2];

	bool interpolate = false;
	bool findEntrancePoint = false;
	bool findExitPoint = false;
	bool findAllCollisions = false;


};