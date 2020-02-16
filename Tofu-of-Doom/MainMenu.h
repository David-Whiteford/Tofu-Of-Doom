#ifndef MAINMENU_SCREEN
#define MAINMENU_SCREEN

#include<SFML\Graphics.hpp>
#include "Enum.h"
#include "Game.h"
#include <string.h>
#include <iostream>
#include "Controller.h"

class Game;

class MainMenu
{
public:
	CXBOXController m_controller;
	MainMenu(Game& t_game, sf::Font t_font);
	~MainMenu();
	//screen functions for the class
	void update(sf::Time t_deltaTime, bool t_soundFX);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	void screenTransitionOn(sf::Time t_deltaTime);
	void screenTransitionOff(sf::Time t_deltaTime);
	void checkPosition();
	void changeGameState(bool t_soundFX);
	void setUpText();
private:
	Game& m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game
	sf::Text m_message; // sf text used for message 
	sf::Sprite m_bg;
	sf::Texture m_bgTexture;
	sf::Clock clock; // starts the clock	
	bool m_continue{ false };
	sf::Time m_timerAnimation = sf::seconds(0.0);
	sf::Time transition_timer = sf::seconds(0.0);
	bool m_startUp = false;
	bool m_moved = false;
	int m_doOnce = 0;
	int space = 0;
	sf::Sprite m_button[5];
	//textures , sound buffers rectangles
	sf::Texture m_buttonTexture;
	sf::RectangleShape m_outlineRect;

	int m_spaceOutline = 20;
	int m_selectPos = 0;
	//all text used
	sf::Text m_playText;
	sf::Text m_optionsText;
	sf::Text m_exitText;

	//timer for button navigation
	sf::Time timer{ sf::seconds(0.0f) };
	sf::Time transitionTimer{ sf::seconds(0.0f) };
	sf::Time transitionTimerOff{ sf::seconds(0.0f) };
};

#endif // Main_Menu
