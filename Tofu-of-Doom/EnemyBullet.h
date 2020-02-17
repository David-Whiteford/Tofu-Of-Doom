#pragma once
#include<SFML/Graphics.hpp>


class EnemyBullet
{
public:
	bool active = false;
	void init(sf::Vector2f pos, sf::Vector2f dir);
	void update();
	EnemyBullet();
	~EnemyBullet();

	sf::CircleShape bullet;
	sf::Vector2f direction;
	float speed = 0.002f;

	int life = 0;
};

