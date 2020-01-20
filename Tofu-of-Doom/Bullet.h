#pragma once



#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Map.h"
#include "DisplayScale.h"

#include "Collider2D.h"

#include "Transform.h"

class Bullet
{
public:

	void bulletInit(sf::Vector2f t__dir, float t_aliveAt, sf::Vector2f t_startPos);
	void setDamageAmount(int t_damage);
	void setActive(bool t_alive);
	void setTimeAliveAt(float t_time);
	bool isActive();
	int getDamageAmount();
	void setSpeed(float t_speed);
	void setDirection(sf::Vector2f t_dir);
	void setPosition(sf::Vector2f t_pos);

	void update();

	sf::CircleShape bulletSprite();



private:
	sf::Time m_time;

	int m_damage = 1;
	bool m_alive = false;

	Transform m_transform;

	float m_radius = 3;

	sf::CircleShape m_bulletShape;

	float m_aliveAt = 0;
	float m_timeToLive = 5;

	float speed = 25;

	sf::Vector2f m_direction = sf::Vector2f(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);

	// direction will need glm and sf vector for game and game world respectively

};