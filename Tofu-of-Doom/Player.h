#pragma once
#pragma once
#include <SFML/Graphics.hpp>
class Player
{

public:
	Player();
	sf::RectangleShape m_player;


	void update();
	void setUpContent();
	void render(sf::RenderWindow& t_window);
	sf::RectangleShape getPlayer();
	void applyDamage();
	int getHealth();


private:
	int m_health = 100;
	int m_damage = 2;
};
