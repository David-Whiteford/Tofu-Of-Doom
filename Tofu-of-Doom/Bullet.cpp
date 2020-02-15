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


	raycast.setRayValues(m_firedFrom, m_direction, 0);
	m_bulletShape.setFillColor(sf::Color::Red);
	m_bulletShape.setRadius(5);

	m_aliveAt = 0;
	m_canDrawRayLine = true;
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



bool Bullet::isActive()
{
	return m_alive;
}

int Bullet::getDamageAmount()
{
	return m_damage;
}

int Bullet::getAliveForTime()
{
	return m_alive;
}



bool Bullet::canDrawBulletTracer()
{
	return m_canDrawRayLine;
}

void Bullet::setSpeed(float t_speed)
{
	speed = t_speed;
}

float Bullet::getSpeed()
{
	return speed;
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

sf::Vector2f Bullet::getDirection()
{
	return m_direction;
}



bool Bullet::checkCollision(sf::Vector2f t_enemyPos, float t_radius)
{
	return raycast.hit(t_enemyPos, t_radius);
}

void Bullet::update()
{
	if (m_alive)
	{
		m_position -= m_direction * speed;
		m_bulletShape.setPosition(m_position);
	}



	if (m_aliveAt > collisionAccuaracyCount)
	{
		m_alive = false;
	}

	m_aliveAt+=1;

}

sf::CircleShape Bullet::bulletSprite()
{
	return m_bulletShape;
}



void Bullet::setCanDrawBulletTracer(bool t_draw)
{
	m_canDrawRayLine = t_draw;
}


sf::Vector2f Bullet::getPosition()
{
	return m_position;
}

int Bullet::getStepAccuruacy()
{
	return collisionAccuaracyCount;
}
