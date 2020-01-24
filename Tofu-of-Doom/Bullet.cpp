#include "Bullet.h"

Bullet::Bullet()
{
	setActive(false);
}

Bullet::~Bullet()
{
}

void Bullet::bulletInit(sf::Vector2f t_dir, float t_aliveAt, sf::Vector2f t_startPos)
{
	setDirection(t_dir);

	setPosition(t_startPos);
	setFiredFromPosition(t_startPos);
	setTimeToLive(1);
	m_bulletShape.setFillColor(sf::Color::Red);
	m_bulletShape.setRadius(5);

	m_time = m_time.Zero;
	m_aliveAt = 0;
	setActive(true);

	line->color = sf::Color::Red;



}

void Bullet::setDamageAmount(int t_damage)
{
	m_damage = t_damage;
}

void Bullet::setActive(bool t_alive)
{
	m_alive = t_alive;
}

void Bullet::setTimeAliveAt(float t_time)
{
	m_aliveAt = t_time;
}

void Bullet::setTimeToLive(float t_time)
{
	m_timeToLive = t_time;
}

bool Bullet::isActive()
{
	return m_alive;
}

int Bullet::getDamageAmount()
{
	return m_damage;
}

void Bullet::setSpeed(float t_speed)
{
	speed = t_speed;
}

void Bullet::setDirection(sf::Vector2f t_dir)
{
	m_direction = t_dir;
}

void Bullet::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
}

void Bullet::setFiredFromPosition(sf::Vector2f t_pos)
{
	m_firedFrom = t_pos;
}

bool Bullet::checkCollision(sf::Vector2f t_enemyPos, float t_radius)
{
	float dist = std::pow((m_bulletShape.getPosition().x - t_enemyPos.x), 2) + std::pow((m_bulletShape.getPosition().y - t_enemyPos.y), 2);

	// Is an expensive call
	return interpolateCollision(t_enemyPos, t_radius);

	if (dist <= (t_radius + m_radius) * (t_radius + m_radius))
	{
		return true;
	}

	return false;
}

void Bullet::update()
{
	m_position -= m_direction * speed;
	m_bulletShape.setPosition(m_position);
	line[1].position = m_position;
	line[0].position = m_firedFrom;


	if (m_aliveAt >= m_timeToLive)
	{
		m_alive = false;
	}

	m_aliveAt+=1;

}

sf::CircleShape Bullet::bulletSprite()
{
	return m_bulletShape;
}

bool Bullet::interpolateCollision(sf::Vector2f t_enemyPos, float t_enemyRadius)
{

	float leftSide = t_enemyPos.x - t_enemyRadius;
	float rightSide = t_enemyPos.x + t_enemyRadius;
	float topSide = t_enemyPos.y - t_enemyRadius;
	float bottomSide = t_enemyPos.y + t_enemyRadius;


	if ((m_firedFrom.x < leftSide && m_position.x < leftSide) ||
		(m_firedFrom.x > rightSide&& m_position.x > rightSide))
	{
		return false;
	}

	if ((m_firedFrom.y < topSide && m_position.y < topSide) ||
		(m_firedFrom.y > bottomSide&& m_position.y > bottomSide))
	{
		return false;
	}
	// compute double area
	float area = std::abs(((m_firedFrom.x - m_position.x) * (t_enemyPos.y - m_position.y)) - ((t_enemyPos.x - m_position.x) * (m_firedFrom.y - m_position.y)));
	area = area * 2;
	// compute the AB segment length
	float D = std::sqrt(std::pow((m_firedFrom.x - m_position.x), 2) + std::pow((m_firedFrom.y - m_position.y), 2));
	float h = area / D;



	if (h <= t_enemyRadius * 2)
	{
		return true;
	}
	return false;


	// Intersection Point in case we wish to have particles on wall
	//// compute the line AB direction vector components
	//float Dx = (t_firedFrom.x - m_position.x) / D;
	//float Dy = (t_firedFrom.y - m_position.y) / D;

	//// compute the distance from A toward B of closest point to C
	//float t = Dx * (t_enemyPos.x - m_position.x) + Dy * (t_enemyPos.y - m_position.y);

	//// t should be equal to sqrt( (Cx-Ax)² + (Cy-Ay)² - h² )

	//// compute the intersection point distance from t
	//float dt = std::sqrt((t_enemyRadius * t_enemyRadius) - (h * h));

	//// compute first intersection point coordinate
	//float Ex = m_position.x + (t - dt) * Dx;
	//float Ey = m_position.y + (t - dt) * Dy;

	//// compute second intersection point coordinate
	//float Fx = m_position.x + (t + dt) * Dx;
	//float Fy = m_position.y + (t + dt) * Dy;


}
