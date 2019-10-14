#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include"Player.h"
#include <math.h>
class EnemyFollower
{

public:
	EnemyFollower();
	sf::RectangleShape m_enemyFollower;

	void update(sf::RectangleShape playerCharacter);
	void setUpContent();
	void render(sf::RenderWindow& t_window);
	void move(sf::RectangleShape t_playerCharacter);
	sf::RectangleShape getFollower();

private:

	sf::Vector2f newDirection;
};

