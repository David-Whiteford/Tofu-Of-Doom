#pragma once
#include <SFML/Graphics.hpp>
class Enemy
{

public:
	Enemy();
	sf::RectangleShape m_enemy;
	
	void update();
	void setUpContent();
	void render(sf::RenderWindow &  t_window);
	sf::RectangleShape getFollower();


private:

};
