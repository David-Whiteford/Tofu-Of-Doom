#ifndef OPTIONS_SCREEN
#define OPTIONS_SCREEN
#include<SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Enum.h"
#include "Game.h"
#include "Controller.h"
#include "MainMenu.h"
#include <string.h>
#include <iostream>
#include "irrKlang.h"

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class Game;


class Options
{
public:
	int sf_Joystick_index{ 0 };
	Options(Game& t_game, sf::Font t_font);
	~Options();
	//screen functions for the class
	void update(sf::Time t_deltaTime, ISoundEngine* bgSoundEngine);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	void navMenu(sf::Time t_deltaTime, ISoundEngine* bgSoundEngine);
	void checkPosition();
	void checkButtonPosition();
	void changeMusicState(ISoundEngine* bgSoundEngine);
	void changeMusicVol(ISoundEngine* bgSoundEngine);
	bool getBackgroundMusic();
	void flashText();
	void navInnerMenu();
	int m_timer{ 0 };
	bool getSoundFX() const { return m_soundFX; }
	//rectangle shapes fo the outline bar the volumn bar the sound fx squiare and check box square 
	sf::RectangleShape m_outlineRect;
	bool m_volumn = false;
	sf::RectangleShape m_volumnBarIn;
	sf::RectangleShape m_volumnBarOuter;
	sf::Sprite m_bg;
	sf::Texture m_bgTexture;
	sf::RectangleShape m_radioBox[2];
	int nextPos{ 0 };
	bool m_moved{ false };
	int m_spaceOutline{ 100 };
	int m_optionsPos{ 0 };
	bool m_pressed{ false };
	bool m_levelSelect = false;
	void setUpText();
	CXBOXController m_controller;

private:
	Game& m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game
	/// <summary>
	/// // sf text used for messages
	/// </summary>
	sf::Text m_volumnMessage;
	sf::Text m_musicMessage;
	sf::Text m_musicmsgOff;
	sf::Text m_musicmsgOn;
	bool m_backgrdMusic = true;
	sf::Time m_optionsTimer{ sf::seconds(0.0f) };//timer for options
	const std::string BACKGROUND_MESSAGE{ "Music" }; // message for background music
	const std::string VOL_MESSAGE{ "Volume" }; // message for background music
	const std::string ON_MSG{ "Turn On" };
	const std::string OFF_MSG{ "Turn Off" };
	// screen timers 
	sf::SoundBuffer m_buffoptionMove;
	sf::Sound m_moveOptionSound;
	sf::Sprite m_button[4];
	int m_offsetX = 0;
	bool m_soundFX = true;
	sf::Texture m_buttonTexture;
	sf::Text m_pressBackMessage; // sf text used for message
};

#endif 
