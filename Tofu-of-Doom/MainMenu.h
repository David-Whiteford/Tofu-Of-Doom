#ifndef MAINMENU_SCREEN
#define MAINMENU_SCREEN

#include<SFML\Graphics.hpp>
#include "Enum.h"
#include "Game.h"
#include <string.h>
#include <iostream>


class Game;

class MainMenu
{
public:

	MainMenu(Game& t_game, sf::Font t_font);
	~MainMenu();
	//screen functions for the class
	void update(sf::Time t_deltaTime,bool t_soundFX);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	
	void screenTransitionOn(sf::Time t_deltaTime);
	void screenTransitionOff(sf::Time t_deltaTime);
	void lightningAnimation(sf::Time t_deltaTime, bool t_soundFX);
	void setUpText();
private:
	Game & m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game
	sf::Text m_message; // sf text used for message 
	sf::Sprite m_bg;
	sf::Texture m_bgTexture;
	
	bool m_continue{ false };
	sf::Time m_timerAnimation = sf::seconds(0.0);
	sf::Time transition_timer = sf::seconds(0.0);
	bool m_startUp = true;
	bool m_movedOption = false;
	int space = 0;
	//Button m_button[4];
	sf::Sprite m_button[5];
	//textures , sound buffers rectangles
	sf::Texture m_buttonTexture;
	sf::RectangleShape outline;
	//sf::SoundBuffer buff;
	//sf::Sound m_moveOptionSound;
	//sf::SoundBuffer buff2;
	//sf::Sound m_selectSound;
	//sf::SoundBuffer buff3;
	//sf::Sound m_thunder;
	int m_spaceOutline = 20;
	int m_selectPos = 0;
	//all text used
	sf::Text m_playText;
	sf::Text m_highScoreText;
	sf::Text m_optionsText;
	sf::Text m_exitText;
	sf::Text m_creditsText;
	//timer for button navigation
	sf::Time timer{ sf::seconds(0.0f) };
};

#endif // Main_Menu
