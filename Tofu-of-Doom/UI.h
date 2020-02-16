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
	UI() {
		healthBorder.setFillColor(sf::Color(0, 0, 0, 190));
		healthBorder.setSize(sf::Vector2f(230, 70));
		healthBorder.setPosition(30, 630);

		ammoBorder.setFillColor(sf::Color(0, 0, 0, 190));
		ammoBorder.setSize(sf::Vector2f(230, 70));
		ammoBorder.setPosition(900, 630);

		if (!m_font.loadFromFile("models/AmazDooMRight.ttf"))
		{
			std::cout << "problem loading font" << std::endl;
		}

		if (!retinaTexture.loadFromFile("gunReticle.png"))
		{
			// error...
		}

		retina.setTexture(retinaTexture);
		retina.setPosition(580, 300);
		retina.setScale(.3f, .3f);

		displayHealth.setFont(m_font);
		displayHealth.setFillColor(sf::Color::Red);
		displayHealth.setPosition(sf::Vector2f(65, 633));
		displayHealth.setCharacterSize(50); // in pixels, not points!
		displayHealth.setScale(1, 1);

		ammo.setFont(m_font);
		ammo.setFillColor(sf::Color::Red);
		ammo.setPosition(sf::Vector2f(920, 633));
		ammo.setCharacterSize(50); // in pixels, not points!
		ammo.setScale(1, 1);

	}

	~UI() {}


	sf::RectangleShape getBorderHealth() { return healthBorder; }
	sf::RectangleShape getBorderAmmo() { return ammoBorder; }
	sf::Text getHealthText() { displayHealth.setString("Health: " + std::to_string(healthTest));  return displayHealth; }
	sf::Text getAmmoText() { ammo.setString(std::to_string(clip) + " / " + std::to_string(reserve));  return ammo; }
	sf::Sprite getRetina() { return retina; }
	void update();
	float x = 0, y = 0;

	void setAmmoTextBullet(int bullet, int _reserve) { clip = bullet; reserve = _reserve; }

private:
	sf::Sprite retina;
	sf::Texture retinaTexture;

	sf::RectangleShape healthBorder;
	sf::RectangleShape ammoBorder;

	sf::Text displayHealth;
	int healthTest = 100;


	sf::Font m_font;

	sf::Text ammo;
	int clip = 3, reserve = 9;


	
};

#endif // !UI_H
