#ifndef CREDITS_SCREEN
#define CREDITS_SCREEN

#include<SFML\Graphics.hpp>
#include "MyEnums.h"
#include "Game.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>


class Game;

class Credits
{
public:

	Credits(Game& t_game, sf::Font t_font);
	~Credits();
	//screen functions for the class
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	void fileOutput();
	void fileNextline();
	int timer{ 0 };
	void checkInput();

private:
	Game& m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game
	
	sf::Text m_creditText;
	sf::Text m_titleText;
	sf::Texture m_texture;
	
	
	std::string line;
	std::string output;
	sf::Time m_transitionTimer{ sf::seconds(0.0f) };
	bool m_continue{ false };
	

};

#endif 

