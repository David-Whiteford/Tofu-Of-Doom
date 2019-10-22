#include "Player.h"

Player::Player()
{
	setUpContent();
}

void Player::update()
{
	//to move player for test
	//will change
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_player.setPosition(m_player.getPosition().x , m_player.getPosition().y - 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_player.setPosition(m_player.getPosition().x , m_player.getPosition().y + 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player.setPosition(m_player.getPosition().x, m_player.getPosition().y - 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player.setPosition(m_player.getPosition().x, m_player.getPosition().y + 1.0f);
	}
}

void Player::setUpContent()
{
	

	m_player.setFillColor(sf::Color::Blue);
	m_player.setSize(sf::Vector2f(100, 50));
	m_player.setOutlineColor(sf::Color::Red);
	m_player.setOutlineThickness(5);
	m_player.setPosition(10, 250);
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_player);
}

sf::RectangleShape Player::getPlayer()
{
	return m_player;
}

void Player::applyDamage()
{
	
	m_health -= m_damage;

}

int Player::getHealth()
{
	return m_health;
}
