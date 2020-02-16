#ifndef UI_H
#define UI_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>

#include "DisplayScale.h"
#include <iostream>

class UI
{
public:
	UI() { bottomBorder.setFillColor(sf::Color(0,0,0,135)); bottomBorder.setSize(sf::Vector2f(720, 80)); 
	
	if (!m_font.loadFromFile("models/AmazDooMRight.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}

	if (!texture.loadFromFile("gunReticle.png"))
	{
		// error...
	}
	
	retina.setTexture(texture);
	retina.setPosition(560, 300);

	retina.setScale(.3f, .3f);

	displayHealth.setFont(m_font);
	displayHealth.setFillColor(sf::Color::Red);
	displayHealth.setPosition(sf::Vector2f(65,633));
	displayHealth.setCharacterSize(50); // in pixels, not points!
	displayHealth.setScale(1,1);
	}
	~UI() {}


	sf::RectangleShape getBorder() { return bottomBorder; }
	sf::Text getText() { displayHealth.setString("Health: " + std::to_string(healthTest));  return displayHealth; }
	sf::Sprite getRetina() { return retina; }
	void update();
	float x = 0, y = 0;

private:
	sf::Sprite retina;
	sf::Texture texture;
	sf::RectangleShape bottomBorder;
	sf::Vector2f offset{ sf::Vector2f(0.0f, 690) };
	sf::Text displayHealth;
	int healthTest = 100;
	sf::Font m_font;


	
};

#endif // !UI_H
