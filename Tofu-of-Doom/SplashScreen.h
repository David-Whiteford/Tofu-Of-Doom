

#ifndef SPLASHSCREEN_SCREEN
#define SPLASHSCREEN_SCREEN
#include "Game.h"
#include<SFML\Graphics.hpp>
#include <string.h>
#include <iostream>


class Game;


class SplashScreen
{
public:

	SplashScreen(Game& t_game, sf::Font t_font);
	~SplashScreen();
	//class functions
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	int timer{ 0 };
	void screenTransitionOff();

private:
	Game& m_game; // refrence to game object 
	sf::Font m_font; // font loaded by game
	sf::Text m_pressstartMessage; // sf text used for message
	// sf text used for title messages
	sf::Text m_titleMessage;
	sf::Text m_titlemessageSecond; // sf text used for message
	sf::Sprite m_backgroundSprite;//background sprite
	sf::Texture m_backgroundTexture; //bgtexture
	int m_timer{ 0 };//timer
	const std::string FIRST_TITLE_MESSAGE{ "TOFU OF" }; // string for message
	const std::string SECOND_TITLE_MESSAGE{ "DOOM" }; // stringfor message
	//size of the message and transition timer
	float msg_size = 55.0f;
	float transition_timer = 0.0f;
	float scaleFactor = 1.0f;
	bool m_continue = false;
	
};

#endif // Splashscreen_SCREEN