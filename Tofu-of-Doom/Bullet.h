#pragma once

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Map.h"
#include "DisplayScale.h"

#include "Raycast.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	Raycast raycast;

	void bulletInit(sf::Vector2f t__dir, float t_aliveAt, sf::Vector2f t_startPos);
	void setDamageAmount(int t_damage);

	void setActive(bool t_alive);
	void setStepCount(int _setStepCounter);

	bool isActive();
	int getDamageAmount();
	int getAliveForTime();

	bool canDrawBulletTracer();
	void setDistanceBetweenSteps(float _distanceBetweenSteps);



	void setDirection(sf::Vector2f t_dir);
	void setPosition(sf::Vector2f t_pos);
	void setFiredFromPosition(sf::Vector2f t_pos);

	sf::Vector2f getDirection();

	bool checkCollision(sf::Vector2f t_enemyPos, float t_radius);
	void update();

	sf::CircleShape bulletSprite(); 


	void setCanDrawBulletTracer(bool t_draw);

	sf::Vector2f getPosition();
	int getStepAccuruacy();
	int getSteps() { return m_stepsTaken; }
	float getDistanceBetweenSteps() { return distanceBetweenSteps; }

	int getMaxStepCount() { return maximumStepCount; }
private:

	int maximumStepCount = 5; // amount of checks between steps
	float distanceBetweenSteps = 399; // distance between checks to big a number could mean we overshoot

	int m_damage = 1;
	bool m_alive = false;
	bool m_canDrawRayLine = false;



	float m_radius = 3;

	sf::CircleShape m_bulletShape;


	int m_stepsTaken = 0;
	


	sf::Vector2f m_direction = sf::Vector2f(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);
	sf::Vector2f m_firedFrom = sf::Vector2f(0, 0);


};