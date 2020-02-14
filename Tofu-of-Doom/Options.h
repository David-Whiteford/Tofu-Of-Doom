#ifndef OPTIONS_SCREEN
#define OPTIONS_SCREEN
#include<SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Enum.h"
#include "Game.h"
#include <string.h>
#include <iostream>


class Game;

class Options
{
public:
	int sf_Joystick_index{ 0 };
	Options(Game& t_game, sf::Font t_font);
	~Options();
	//screen functions for the class
	void update(sf::Time t_deltaTime, sf::Music& t_bgMusic);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	void navMenu(sf::Time t_deltaTime, sf::Music& t_bgMusic);
	void adjustVolumn(sf::Music& t_backgroundMusic);
	void changeLevelSelect();
	void flashText();
	int m_timer{ 0 };
	bool getSoundFX() const { return m_soundFX; }
	//rectangle shapes fo the outline bar the volumn bar the sound fx squiare and check box square 
	sf::RectangleShape m_outlineRect;
	sf::RectangleShape m_volumnBarIn;
	sf::RectangleShape m_volumnBarOuter;
	sf::RectangleShape m_selectSoundSquare;
	sf::RectangleShape m_radioBox[3];
	int nextPos{ 0 };
	bool m_moved{ false };
	int m_spaceOutline{ 100 };
	int m_optionsPos{ 0 };
	bool m_pressed{ false };
	bool m_levelSelect = false;
private:
	Game& m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game
	/// <summary>
	/// // sf text used for messages
	/// </summary>
	sf::Text m_volumnMessage;
	sf::Text m_musicMessage;
	

	sf::Time m_optionsTimer{ sf::seconds(0.0f) };//timer for options
	const std::string BACKGROUND_MESSAGE{ "Sound FX" }; // message for background music
	const std::string VOL_MESSAGE{ "Volume" }; // message for background music
	// screen timers 
	sf::SoundBuffer m_buffoptionMove;
	sf::Sound m_moveOptionSound;

	bool m_soundFX = true;

};

#endif 
