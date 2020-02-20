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
	UI(sf::RenderWindow &t_window) : window( t_window)
	{
		
		healthBorder.setFillColor(sf::Color(0, 0, 0, 190));
		healthBorder.setSize(sf::Vector2f(230, 70));
		healthBorder.setPosition(t_window.getSize().x * .15f, t_window.getSize().y  -t_window.getSize().y * .1f);

		ammoBorder.setFillColor(sf::Color(0, 0, 0, 190));
		ammoBorder.setSize(sf::Vector2f(230, 70));
		ammoBorder.setPosition(sf::Vector2f(t_window.getSize().x - t_window.getSize().x * .23f, t_window.getSize().y - t_window.getSize().y * .1f));

		if (!m_font.loadFromFile("fonts/AmazDooMRight.ttf"))
		{
			std::cout << "Error loading font!" << std::endl;
		}

		if (!retinaTexture.loadFromFile("images/gunReticle.png"))
		{
			// error...
		}

		retina.setTexture(retinaTexture);
		retina.setPosition(t_window.getSize().x/2, t_window.getSize().y/2);
		retina.setScale(.3f, .3f);

		displayHealth.setFont(m_font);
		displayHealth.setFillColor(sf::Color::Red);
		displayHealth.setPosition(sf::Vector2f(t_window.getSize().x * .17f, t_window.getSize().y - t_window.getSize().y*.1f));
		displayHealth.setCharacterSize(50); // in pixels, not points!
		displayHealth.setScale(1, 1);

		ammo.setFont(m_font);
		ammo.setFillColor(sf::Color::Red);
		ammo.setPosition(sf::Vector2f(t_window.getSize().x - t_window.getSize().x *.2f, t_window.getSize().y - t_window.getSize().y *.1f));
		ammo.setCharacterSize(50); // in pixels, not points!
		ammo.setScale(1, 1);

	}

	~UI() {}

	sf::RenderWindow& window;
	sf::RectangleShape getBorderHealth() { return healthBorder; }
	sf::RectangleShape getBorderAmmo() { return ammoBorder; }
	sf::Text getHealthText() { displayHealth.setString("Health: " + std::to_string(health));  return displayHealth; }
	sf::Text getAmmoText() { ammo.setString(std::to_string(clip) + " / " + std::to_string(reserve));  return ammo; }
	sf::Sprite getRetina() { return retina; }
	void update();
	void setHealth(int t_value) { health = t_value; }
	float x = 0, y = 0;

	void setAmmoTextBullet(int bullet, int _reserve) { clip = bullet; reserve = _reserve; }

private:
	sf::Sprite retina;
	sf::Texture retinaTexture;

	sf::RectangleShape healthBorder;
	sf::RectangleShape ammoBorder;

	sf::Text displayHealth;
	int health = 100;


	sf::Font m_font;

	sf::Text ammo;
	int clip = 3, reserve = 9;


	
};

#endif // !UI_H
