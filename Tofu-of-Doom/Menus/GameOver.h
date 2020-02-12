
#ifndef GAMEOVER_SCREEN
#define GAMEOVER_SCREEN

#include <SFML/Graphics.hpp>
#include "MyEnums.h"
#include "Game.h"
#include <string.h>
#include <iostream>



class Game;

class GameOver
{
public:

	GameOver(Game& t_game, sf::Font t_font);
	~GameOver();
	//screen functions for the class
	int update(int t_score, sf::Time t_deltaTime, sf::Event &event , int t_writeOnce);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	int timer{ 0 };
	void nameInput(int t_score);
	sf::String getName();
	void timers(sf::Time dt);
	void resetnameString();
	sf::RectangleShape m_outline;
private:
	Game& m_game; // refrence to game object used to set game state
	
	sf::Font m_font; // font loaded by game
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_arrowTexture;
	sf::Sprite m_arrowSprite;
	//text for all messages
	sf::Text m_playerscoreText;
	sf::Text m_playersnameText;
	sf::Text m_restartgameTxt;
	sf::Text m_playernameText;
	sf::Text m_playersname;
	//player name initial string
	sf::String m_playerName{ "AAAAAA" };
	//array of characters
	char m_alphabetChar[27];
	//index of the character
	int m_charNameIndex{ 0 };
	int i = 0;
	//timers 
	sf::Time m_transitionTimer{ sf::seconds(0.0f) };
	sf::Time m_timer{ sf::seconds(0.0f) };
	sf::Time m_nameTimer{ sf::seconds(0.0f) };
	//bools used for movind , continuing to next restart and move name
	bool m_moved{ false };
	bool m_continue{false};
	bool m_restart{ false };
	bool m_nameMoved{ false };
};

#endif 
