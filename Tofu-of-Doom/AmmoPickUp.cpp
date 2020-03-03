#include "AmmoPickUp.h"

AmmoPickUp::AmmoPickUp(sf::RenderWindow& t_window) : m_window(t_window)
{
	m_sprite.setRadius(m_radius);
	m_sprite.setFillColor(sf::Color::Yellow);
	setAlive(false);
}

AmmoPickUp::~AmmoPickUp()
{
}

float AmmoPickUp::getRadius()
{
	return m_radius;
}

sf::CircleShape AmmoPickUp::getSprite()
{
	return m_sprite;
}

sf::Vector2f AmmoPickUp::getPosition()
{
	return m_position;
}

void AmmoPickUp::setPosition(sf::Vector2f m_pos)
{
	m_position = m_pos;
}

void AmmoPickUp::setAlive(bool t_alive)
{
	m_alive = t_alive;
}

void AmmoPickUp::draw()
{
	m_sprite.setPosition(m_position);
	m_window.draw(m_sprite);
}

bool AmmoPickUp::isAlive()
{
	return m_alive;
}
