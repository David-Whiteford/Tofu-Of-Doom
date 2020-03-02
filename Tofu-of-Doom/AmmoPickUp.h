#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "DisplayScale.h"
#include <stdlib.h>
#include "Globals.h"

class AmmoPickUp
{
public:

	AmmoPickUp(sf::RenderWindow& t_window);
	~AmmoPickUp();



	float getRadius();
	sf::CircleShape getSprite();


	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f m_pos);

	void setAlive(bool t_alive);

	void draw();

	bool isAlive();






private:

	bool m_alive;





	sf::CircleShape m_sprite;

	sf::RenderWindow& m_window;




	float m_radius = 23;


	sf::Vector2f m_position = sf::Vector2f(0, 0);





};
