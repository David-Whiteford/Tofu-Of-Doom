#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f t_position);
	void setPosition(float t_x, float t_y);
	int getHealth();
	void setHealth(int t_healthAmount);
	void increaseHealth(int t_healthAmount);
	void decreaseHealth(int t_healthAmount);
	sf::CircleShape getSprite();
	void update();

private:
	sf::CircleShape m_playerCircle;
	int m_health{ 100 };
	sf::Vector2f m_position;
};

#endif // !PLAYER_H
