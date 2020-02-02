#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "DisplayScale.h"
#include "Transform.h"

#include "Path.h"
#include <stdlib.h>
#include <ctime>

class Enemy
{
public:
	Enemy(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position);
	~Enemy();

	void enemyInit();
	void setDamageAmount(int t_damage);
	int getDamageAmount();
	void setSpeed(float t_speed);
	void setDirection(sf::Vector2f t_dir);
	void setPosition(sf::Vector2f t_pos);
	void update(sf::CircleShape t_player);
	void enemyMovement();
	void enemyFollowPlayer();
	void moveEnemy();
	void draw();
	int getRandNode();

private:
	float m_speedEn{ 5.0f };
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
	Path* m_gamePath = new Path(m_window);
	bool follow = false;
	std::vector<int> m_startNodes;
	std::vector<int> m_endNodes;
	int startNode = 103;
	int endNode = 2237;
	sf::CircleShape m_enemies;
	bool m_alive = false;
	float m_radius = 3;
	int m_aliveAt = 0;
	float m_timeToLive = 2;
	sf::Vector2f m_direction = sf::Vector2f(0, 0);
	sf::Vector2f m_position = sf::Vector2f(0, 0);
	sf::Vector2f m_firedFrom = sf::Vector2f(0, 0);
	std::vector<sf::RectangleShape> m_walls;
	
	sf::Time& m_deltaTime;
};
#endif // !ENEMY_H
