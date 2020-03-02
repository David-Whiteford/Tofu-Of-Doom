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
		healthBorder.setPosition(t_window.getSize().x * .15f, t_window.getSize().y - t_window.getSize().y * .1f);
		
		enemyRemainBorder.setFillColor(sf::Color(0, 0, 0, 190));
		enemyRemainBorder.setSize(sf::Vector2f(230, 70));
		enemyRemainBorder.setPosition(t_window.getSize().x * .15f, t_window.getSize().y - t_window.getSize().y * .9f);

		ammoBorder.setFillColor(sf::Color(0, 0, 0, 190));
		ammoBorder.setSize(sf::Vector2f(230, 70));
		ammoBorder.setPosition(sf::Vector2f(t_window.getSize().x - t_window.getSize().x * .23f, t_window.getSize().y - t_window.getSize().y * .1f));

		scoreBorder.setFillColor(sf::Color(0, 0, 0, 190));
		scoreBorder.setSize(sf::Vector2f(230, 70));
		scoreBorder.setPosition(sf::Vector2f(t_window.getSize().x - t_window.getSize().x * .23f, t_window.getSize().y * .1f));
		

		if (!m_font.loadFromFile("fonts/AmazDooMRight.ttf"))
		{
			std::cout << "Error loading font!" << std::endl;
		}

		if (!retinaTexture.loadFromFile("images/gunReticle.png"))
		{
			// error...
		}
		if (!vignetteTexture.loadFromFile("images/Hurt.png"))
		{
			// error...
		}

		retina.setTexture(retinaTexture);
		retina.setPosition(t_window.getSize().x / 2, t_window.getSize().y / 2);
		retina.setScale(.3f, .3f);

		vignetteSprite.setTexture(vignetteTexture);
		vignetteSprite.setPosition(0, 0);
		vignetteSprite.setScale(1, 1);

		displayHealth.setFont(m_font);
		displayHealth.setFillColor(sf::Color::Red);
		displayHealth.setPosition(sf::Vector2f(t_window.getSize().x * .17f, t_window.getSize().y - t_window.getSize().y * .1f));
		displayHealth.setCharacterSize(50); // in pixels, not points!
		displayHealth.setScale(1, 1);

		scoreVal.setFont(m_font);
		scoreVal.setFillColor(sf::Color::Red);
		scoreVal.setPosition(sf::Vector2f(t_window.getSize().x - t_window.getSize().x * .2f, t_window.getSize().y - t_window.getSize().y * .9f));
		scoreVal.setCharacterSize(50); // in pixels, not points!
		scoreVal.setScale(1, 1);

		displayEnemyRemaining.setFont(m_font);
		displayEnemyRemaining.setFillColor(sf::Color::Red);
		displayEnemyRemaining.setPosition(sf::Vector2f(t_window.getSize().x * .17f, t_window.getSize().y - t_window.getSize().y * .9f));
		displayEnemyRemaining.setCharacterSize(50); // in pixels, not points!
		displayEnemyRemaining.setScale(1, 1);

		ammo.setFont(m_font);
		ammo.setFillColor(sf::Color::Red);
		ammo.setPosition(sf::Vector2f(t_window.getSize().x - t_window.getSize().x *.2f, t_window.getSize().y - t_window.getSize().y *.1f));
		ammo.setCharacterSize(50); // in pixels, not points!
		ammo.setScale(1, 1);

	}

	~UI() {}

	sf::RenderWindow& window;

	// Borders
	sf::RectangleShape getBorderHealth() { return healthBorder; }
	sf::RectangleShape getBorderRemainingEnemy() { return enemyRemainBorder; }
	sf::RectangleShape getBorderAmmo() { return ammoBorder; }
	sf::RectangleShape getScoreAmmo() { return scoreBorder; }

	// Text
	sf::Text getHealthText() { displayHealth.setString("Health: " + std::to_string(health));  return displayHealth; }
	sf::Text getEnemyRemainingText(int t_remain) { displayEnemyRemaining.setString("Enemy: " + std::to_string(t_remain));  return displayEnemyRemaining; }
	sf::Text getAmmoText() { ammo.setString(std::to_string(clip) + " / " + std::to_string(reserve));  return ammo; }
	sf::Text getScoreText() { scoreVal.setString("Score: " + std::to_string(score));  return scoreVal; }
	sf::Sprite getRetina() { return retina; }
	sf::Sprite getVignette() { return vignetteSprite; }
	void update();
	void setHealth(int t_value) { health = t_value; }
	float x = 0, y = 0;
	void setScore(int t_value) { score = t_value; }
	void setAmmoTextBullet(int bullet, int _reserve) { clip = bullet; reserve = _reserve; }

private:
	sf::Sprite retina;
	sf::Texture retinaTexture;

	sf::RectangleShape healthBorder;
	sf::RectangleShape ammoBorder;
	sf::RectangleShape scoreBorder;
	sf::RectangleShape enemyRemainBorder;

	sf::Sprite vignetteSprite;
	sf::Texture vignetteTexture;
	sf::Text scoreVal;
	sf::Text displayHealth;
	sf::Text displayEnemyRemaining;
	int health = 100;


	sf::Font m_font;

	sf::Text ammo;
	int clip = 3, reserve = 9;
	int score = 0;

	
};

#endif // !UI_H
