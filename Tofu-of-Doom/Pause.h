#ifndef PAUSE_SCREEN
#define PAUSE_SCREEN
#include "Game.h"
#include<SFML\Graphics.hpp>
#include <string.h>
#include <iostream>
#include "Controller.h"


class Game;


class PauseScreen
{
public:
	CXBOXController m_controller;
	PauseScreen(Game& t_game, sf::Font t_font);
	~PauseScreen();
	//class functions
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpContent();


	

private:
	Game& m_game; // refrence to game object 
	sf::Font m_font; // font loaded by game
	sf::Text m_pressstartMessage; // sf text used for message
	sf::Text m_pressBackMessage; // sf text used for message
	// sf text used for title messages
	sf::Sprite m_backgroundSprite;//background sprite
	sf::Texture m_backgroundTexture; //bgtexture

	const std::string BACK_MESSAGE{ "Press Back to return to Menu" }; // string for message
	const std::string PAUS_MESSAGE{ "Press pause to continue" }; // stringfor message
	//size of the message and transition timer
	float msg_size = 55.0f;

	int m_do_once = 0;
	

};

#endif