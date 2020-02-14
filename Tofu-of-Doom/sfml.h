#ifndef SFML_SCREEN
#define SFML_SCREEN

#include<SFML\Graphics.hpp>
#include "Game.h"
#include <string.h>
#include <iostream>

class Game;

class SFML
{
public:

	SFML(Game& t_game, sf::Font t_font, sf::Sprite t_sfmlSprite);
	~SFML();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);
	void setUpContent();
	void screenAnimation();
	int timer{ 0 };

private:
	Game& m_game; // refrence to game object used to set game state
	sf::Font m_font; // font loaded by game
	sf::Text m_licenceMessage; // sf text used for message
	sf::Sprite m_sfmlSprite;
	sf::Time m_cumulativeTime;
	AnimationState m_animationState;
	int m_keyFrameLevel{ 100 }; // keyframe afer rotation
	//screen timer
	int m_timer{ 250 };
	const std::string First_MESSAGE{ "Made Using SFML" }; // message for sfml message


};

#endif // SFML_SCREEN
