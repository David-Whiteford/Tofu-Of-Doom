#include "ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(sf::RenderWindow& t_window) : m_window(t_window)
{
	m_bulletShape.setFillColor(sf::Color::Blue);
	m_bulletShape.setRadius(m_radius);

}

ProjectileEnemy::~ProjectileEnemy()
{
	delete this;
}

void ProjectileEnemy::init(sf::Vector2f startPosition, sf::Vector2f moveDirection)
{
	m_position = startPosition;
	m_direction = moveDirection / s_displayScale;

	m_direction = m_direction / sqrtf(m_direction.x * m_direction.x - m_direction.y * m_direction.y);
	m_aliveAt = 0;
	m_alive = true;
}

void ProjectileEnemy::setDamageAmount(int t_damage)
{
	damageAmount = t_damage;
}

int ProjectileEnemy::getDamageAmount()
{
	return damageAmount;
}

void ProjectileEnemy::update(sf::Time t_deltaTime)
{
	m_position += sf::Vector2f(m_direction.x * (m_speed), m_direction.y * (m_speed));

	m_bulletShape.setPosition(m_position);
	m_aliveAt++;

	if (m_aliveAt > m_timeToLive)
	{
		m_alive = false;
		m_aliveAt = 0;
	}
}

float ProjectileEnemy::getRadius()
{
	return m_radius;
}

sf::CircleShape ProjectileEnemy::getSprite()
{
	return m_bulletShape;
}

sf::Vector2f ProjectileEnemy::getPosition()
{
	return m_position;
}

void ProjectileEnemy::setAlive(bool t_alive)
{
	m_alive = t_alive;
}

void ProjectileEnemy::draw()
{
	m_window.draw(m_bulletShape);
}

bool ProjectileEnemy::isAlive()
{
	return m_alive;
}
