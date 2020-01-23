#include "Bullet.h"

void Bullet::bulletInit(sf::Vector2f t_dir, float t_aliveAt, sf::Vector2f t_startPos)
{
	setDirection(t_dir);
	setTimeAliveAt(t_aliveAt);
	setPosition(t_startPos);

	m_bulletShape.setFillColor(sf::Color::Red);
	m_bulletShape.setRadius(5);

	m_time = m_time.Zero;
	m_aliveAt = 0;
	setActive(true);



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

bool Bullet::checkCollision(sf::Vector2f t_enemyPos, float t_radius)
{
	float dist = std::pow((m_bulletShape.getPosition().x - t_enemyPos.x), 2) + std::pow((m_bulletShape.getPosition().y - t_enemyPos.y), 2);

	if (dist <= (t_radius + m_radius) * (t_radius + m_radius))
	{
		return true;
	}
	return false;
}

void Bullet::update()
{
	m_aliveAt++;
	m_position -= m_direction * speed;
	m_bulletShape.setPosition(m_position);

	if ( m_aliveAt > m_timeToLive)
	{
		m_alive = false;
	}
}

sf::CircleShape Bullet::bulletSprite()
{
	return m_bulletShape;
}
