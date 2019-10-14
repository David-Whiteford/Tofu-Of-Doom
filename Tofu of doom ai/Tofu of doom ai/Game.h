#pragma once
#include "ScreenSize.h"
#include "SFML/Graphics.hpp"
#include "enemy.h"
#include "EnemyFollower.h"

class Game
{
public:

	Game();
	Enemy m_enemy;
	EnemyFollower m_enemyFollower;
	Player m_player;
	void run();
	void processEvents();
	void update(double dt);
	void processGameEvents(sf::Event& event);
	void render();
	void collisions();
private:
	sf::RenderWindow m_window;
	sf::RectangleShape m_playerRect;
	sf::RectangleShape m_testRect;
};
