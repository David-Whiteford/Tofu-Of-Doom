#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "DisplayScale.h"
#include <stdlib.h>
#include "Globals.h"

class ProjectileEnemy : public GameObject
{
public:

	ProjectileEnemy(sf::RenderWindow& t_window);
	~ProjectileEnemy();



	void init(sf::Vector2f startPosition, sf::Vector2f moveDirection);
	void setDamageAmount(int t_damage);
	int getDamageAmount();

	void update(sf::Time t_deltaTime);

	//void draw();

	float getRadius();
	sf::CircleShape getSprite();


	sf::Vector2f getPosition();

	void setAlive(bool t_alive);

	void draw();

	bool isAlive();



	bool canRender = true;


	GameObject* myGameObject;

private:

	bool m_alive;
	float m_speed = 5.0f;

	int damageAmount = 10;



	sf::Time m_time;




	sf::CircleShape m_bulletShape;

	sf::RenderWindow& m_window;




	float m_radius = 23; 
	int m_aliveAt = 0;
	float m_timeToLive = 400;

	sf::Vector2f m_direction = sf::Vector2f(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);





};
