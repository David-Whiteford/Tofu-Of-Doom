#include "enemy.h"

Enemy::Enemy()
{
	setUpContent();
}

void Enemy::update()
{
}

void Enemy::setUpContent()
{
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setSize(sf::Vector2f(100, 50));
	m_enemy.setOutlineColor(sf::Color::Red);
	m_enemy.setOutlineThickness(5);
	m_enemy.setPosition(10, 20);
}

void Enemy::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_enemy);
}
sf::RectangleShape Enemy::getFollower()
{
	return m_enemy;
}

