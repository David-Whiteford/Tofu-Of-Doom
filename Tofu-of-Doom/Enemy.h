#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "DisplayScale.h"
#include "Transform.h"
#include "Raycast.h"
#include "Path.h"
#include "Player.h"
#include <stdlib.h>
#include <ctime>
#include "Globals.h"

class Enemy : public GameObject
{
public:
	Enemy(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position , Path* t_gamePath);
	~Enemy();
	Player m_player;
	void enemyInit();
	void setDamageAmount(int t_damage);
	int getDamageAmount();
	void setSpeed(float t_speed);
	void setDirection(sf::Vector2f t_dir);
	void setPosition(sf::Vector2f t_pos);
	void update(sf::CircleShape t_player, sf::Time t_deltaTime);
	void enemyMovement(sf::Time t_deltaTime);
	void enemyFollowPlayer();
	void moveEnemy(sf::Time t_deltaTime);
	void draw();

	float getRadius();
	sf::CircleShape getSprite();
	int getRandNode();
	sf::Vector2f getPosition();

	void setAlive(bool t_alive);
	void setDead();
	bool isAlive();


	float startSize = 0.5f;
	float currentSize = 0.5f;

	float reduceSpeed = 0.03f;
	bool canRender = true;


	GameObject* myGameObject;

private:
	Raycast m_rayCast;
	bool m_alive;
	float m_speedEn = 0.18f;
	sf::Time m_time;
	int m_currentNode = 0;
	int m_endNode = 0;
	int m_playerNode = 0;
	int m_enemyNode = 0;

	Transform m_transform;
	Transform::Position enemyPos;
	Transform::Position graphPos;

	sf::CircleShape m_enemy;
	std::vector<Node*> graphPath;
	sf::RenderWindow& m_window;
	Path *m_gamePath;
	sf::Vector2f graphPathVec;
	bool follow = false;
	std::vector<int> m_startNodes;
	std::vector<int> m_endNodes;


	int m_doOncePatrol = 0;
	int m_doOnceSeek = 0;
	int startNode = 103;
	int endNode = 2450;


	float m_radius = 33; // makes hitting enmies easier
	int m_aliveAt = 0;
	float m_timeToLive = 2;
	sf::Vector2f m_direction = sf::Vector2f(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);
	sf::Vector2f m_firedFrom = sf::Vector2f(0, 0);
	std::vector<sf::RectangleShape> m_walls;
	enum class EnemyBehaviour
	{
		PATROL_MAP,
		SEEK_PLAYER,
		STOP,
		RETREAT
	}
	m_enemyBehaviour;
	sf::Time& m_deltaTime;


};
