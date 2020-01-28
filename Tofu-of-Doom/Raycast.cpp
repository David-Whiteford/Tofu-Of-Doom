#include "Raycast.h"

Raycast::Raycast()
{
	interpolate = true;
}

Raycast::~Raycast()
{
}

void Raycast::setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length)
{
	m_positon = t_startPosition;
	m_direction = -t_direction;
	m_rayLength = t_length;
}

bool Raycast::circleHit(sf::Vector2f t_targetPosition, float t_targetRadius)
{


	float leftSide = t_targetPosition.x - t_targetRadius;
	float rightSide = t_targetPosition.x + t_targetRadius;
	float topSide = t_targetPosition.y - t_targetRadius;
	float bottomSide = t_targetPosition.y + t_targetRadius;

	sf::Vector2f endPoint = m_positon + (m_direction * m_rayLength);


	if ((m_positon.x < leftSide && endPoint.x < leftSide) ||
		(m_positon.x > rightSide&& endPoint.x > rightSide))
	{
		return false;
	}

	if ((m_positon.y < topSide && endPoint.y < topSide) ||
		(m_positon.y > bottomSide&& endPoint.y > bottomSide))
	{
		return false;
	}

	// compute double area
	float area = std::abs(((m_positon.x - endPoint.x) * (t_targetPosition.y - endPoint.y)) - ((t_targetPosition.x - endPoint.x) * (m_positon.y - endPoint.y)));
	area = area * 2;
	// compute the AB segment length
	float D = std::sqrt(std::pow((m_positon.x - endPoint.x), 2) + std::pow((m_positon.y - endPoint.y), 2));
	float h = area / D;



	if (h >= t_targetRadius * 2)
	{
		return false;
	}
	else
	{
		if (!interpolate)
		{
			return true;
		}



		float dist = std::sqrt(std::pow((t_targetPosition.x - m_positon.x), 2) + std::pow((t_targetPosition.y - m_positon.y), 2));
		// Intersection Point in case we wish to have particles on wall

		dist -= t_targetRadius;


		m_rayLength = dist;


		return true;

	}
}

sf::VertexArray Raycast::drawRay()
{
	//float normalDiv = std::sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	sf::VertexArray ray(sf::LinesStrip, 2);
	ray[0].position = m_positon;

	ray[1].position = m_positon + (m_direction * m_rayLength);
	

	return ray;
}

void Raycast::addToHitObjects(sf::CircleShape* t_enemy)
{
	hitObjects.push(t_enemy);
}

std::queue<sf::CircleShape*> Raycast::getHitObjects()
{
	return hitObjects;
}

void Raycast::getClosest()
{
	bool first = true;
	while (hitObjects.size() > 0)
	{
		if (first)
		{
			closest = hitObjects.front();
			hitObjects.pop();
		}
		else
		{
			float dist1 = std::sqrt((std::pow((m_positon.x - closest->getPosition().x), 2) + (std::pow((m_positon.y - closest->getPosition().y), 2))));
			float dist2 = std::sqrt((std::pow((m_positon.x - hitObjects.front()->getPosition().x), 2) + (std::pow((m_positon.y - hitObjects.front()->getPosition().y), 2))));

			if (dist2 < dist1)
			{
				closest = hitObjects.front();
			}
			hitObjects.pop();
		}
	}
	sf::Vector2f newPos = sf::Vector2f(200, 200);
	closest->setPosition(newPos);
}

bool Raycast::isInterpolating()
{
	return interpolate;
}
