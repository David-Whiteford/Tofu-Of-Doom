#ifndef BOSS_H
#define BOSS_H
#include<SFML\Graphics.hpp>
#include <string.h>
#include <iostream>
#include "Transform.h"
#include "Raycast.h"
#include "Path.h"

class Boss
{
public:
	
	Boss(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position, Path* t_gamePath);
	~Boss();
	//class functions
	void update(sf::Time t_deltaTime, sf::CircleShape t_player);
	void setHealth(int t_healthAmount);
	int getHealth();
	void setUpBoss();
	void render();
	void decreaseHealth(int t_healthAmount);
	void enemyMovement(sf::Time t_deltaTime);
	void moveEnemy(sf::Time t_deltaTime);
	void setAlive(bool t_alive);
	void setDead();
	bool isAlive();
	float getRadius();
	sf::CircleShape getSprite();
	int getRandNode();
	sf::Vector2f getPosition();

private:
	Path* m_gamePath;
	float m_speedEn = 0.18f;
	std::vector<Node*> graphPath;
	sf::CircleShape m_bossCircle;
	int m_enemyNode = 0;
	int m_playerNode = 0;
	int m_health = 500;
	sf::Time m_bossTimer = sf::seconds(0.0);
	sf::RenderWindow& m_window;
	sf::Time& m_deltaTime;
	sf::Vector2f m_position;
	Transform m_transform;
	Transform::Position enemyPos;
	Transform::Position graphPos;
	sf::Vector2f graphPathVec;
	
	float m_radius = 33; // makes hitting enmies easier

	std::vector<int> m_startNodes;
	std::vector<int> m_endNodes;
	bool m_alive;
	int m_doOncePatrol = 0;
	int m_doOnceSeek = 0;
	enum class EnemyBehaviour
	{
		PATROL,
		SEEK_PLAYER,
		STOP,
		RETREAT
	}
	m_enemyBehaviour;
};

#endif // End Boss