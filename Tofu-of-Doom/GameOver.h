#ifndef GAMEOVER_SCREEN
#define GAMEOVER_SCREEN
#include "Game.h"
#include<SFML\Graphics.hpp>
#include <string.h>
#include <iostream>
#include "Controller.h"


class Game;


class GameOver
{
public:
	CXBOXController m_controller;
	GameOver(Game& t_game, sf::Font t_font);
	~GameOver();
	//class functions
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	sf::Time transitionTimer{ sf::seconds(0.0f) };
	sf::Time screenTimer{ sf::seconds(0.0f)};
	void screenTransitionOn(sf::Time t_deltaTime);
	void resetTime();
	void setFontText(sf::Font t_font, std::string FIRST_TITLE_MESSAGE, sf::Texture m_backgroundTexture);

private:
	Game& m_game; // refrence to game object 
	sf::Font m_font; // font loaded by game
	// sf text used for title messages
	sf::Text m_titleMessage;
	sf::Text m_titlemessageSecond; // sf text used for message
	sf::Sprite m_backgroundSprite;//background sprite
	sf::Texture m_backgroundTexture; //bgtexture
	int m_timer{ 0 };//timer
	const std::string FIRST_TITLE_MESSAGE{ "YOU HAVE DIED" }; // string for message
	const std::string SECOND_TITLE_MESSAGE{ "GAME OVER" }; // stringfor message
	//size of the message and transition timer
	float msg_size = 55.0f;
	float scaleFactor = 1.0f;
	
	int m_do_once = 0;
	float elapsed1{ 0.0f };

};

#endif // Splashscreen_SCREEN