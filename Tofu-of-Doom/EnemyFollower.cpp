#include "EnemyFollower.h"

EnemyFollower::EnemyFollower()
{
	setUpContent();

}

void EnemyFollower::update(sf::RectangleShape playerCharacter)
{
	move(playerCharacter);
}

void EnemyFollower::setUpContent()
{
	m_enemyFollower.setFillColor(sf::Color::Green);
	m_enemyFollower.setSize(sf::Vector2f(100, 50));
	m_enemyFollower.setOutlineColor(sf::Color::Red);
	m_enemyFollower.setOutlineThickness(5);
	m_enemyFollower.setPosition(200, 20);
}

void EnemyFollower::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_enemyFollower);
}

void EnemyFollower::move(sf::RectangleShape t_playerCharacter)
{
	/*
	sf::Vector2f direction = t_playerCharacter.getPosition() - m_enemyFollower.getPosition();
	newDirection = Vector2f.Normalize(direction);*/
	m_enemyFollower.setPosition(t_playerCharacter.getPosition().x - m_enemyFollower.getPosition().x 
		, t_playerCharacter.getPosition().y - m_enemyFollower.getPosition().y) ;

}
sf::RectangleShape EnemyFollower::getFollower()
{
	return m_enemyFollower;
}

