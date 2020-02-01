#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow& t_window, sf::Time& t_deltaTime)
	: m_window(t_window), m_deltaTime(t_deltaTime)
{
	m_endNodes.push_back(252);
	m_endNodes.push_back(491);
	m_endNodes.push_back(855);
	m_endNodes.push_back(1955);
	m_endNodes.push_back(1420);
	m_endNodes.push_back(2353);
	m_endNodes.push_back(681);
	m_endNodes.push_back(2237);
	enemyInit();

}

Enemy::~Enemy()
{
}

void Enemy::enemyInit()
{
	m_enemies.push_back(m_enemy);
	m_enemies.push_back(m_enemy);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].setRadius(25.0f);
		m_enemies[i].setFillColor(sf::Color::Red);
		m_enemies[i].setOrigin(sf::Vector2f(25.0f, 25.0f));
		m_enemies[i].setPosition(100, 800); // Test starting position
	}
	//Astar
	m_gamePath->initAStar(m_walls);
	m_gamePath->setPath();
	graphPath = m_gamePath->getGraphPath();
}

void Enemy::setDamageAmount(int t_damage)
{
	
}

int Enemy::getDamageAmount()
{
	return 0;
}

void Enemy::setSpeed(float t_speed)
{
}

void Enemy::setDirection(sf::Vector2f t_dir)
{
}

void Enemy::setPosition(sf::Vector2f t_pos)
{
}

void Enemy::update(sf::CircleShape t_player)
{
	//sets the node the player and the enemy are in
	m_playerNode = m_gamePath->nodePos(t_player.getPosition());
	m_enemyNode = m_gamePath->nodePos(m_enemies.front().getPosition());
	std::cout << "Player in Node:  " << m_playerNode << std::endl;
	//std::cout << "Enemy in Node:  " << m_enemyNode << std::endl;

	
	sf::Vector2f offSet = sf::Vector2f(150, 150);
	if (t_player.getPosition().x >= m_enemies.front().getPosition().x - offSet.x
		&& t_player.getPosition().x <= m_enemies.front().getPosition().x + offSet.x
		&& t_player.getPosition().y >= m_enemies.front().getPosition().y - offSet.y
		&& t_player.getPosition().y <= m_enemies.front().getPosition().y + offSet.y)
	{
		std::cout << "In enemy Range" << std::endl;
		follow = true;
		graphPath.resize(0);
	}
	else
	{
		follow = false;
	}
	enemyMovement();
}

void Enemy::draw()
{
	m_window.draw(m_enemies.front());
}
void Enemy::moveEnemy()
{

	sf::Vector2f graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);
	sf::Vector2f moveTo = m_transform.moveTowards(m_enemies.front().getPosition(), graphPathVec, m_speedEn);
	m_enemies.front().setPosition(moveTo);
	if (m_enemies.front().getPosition().x == graphPath.back()->m_data.m_x &&
		m_enemies.front().getPosition().y == graphPath.back()->m_data.m_y)
	{
		graphPath.pop_back();
	}

}
/// <summary>
/// Moves the enemy
/// </summary>
void Enemy::enemyMovement()
{
	if (follow == false)
	{
		//graphPath = m_gamePath->getGraphPath();
		if (graphPath.empty() == false)
		{
			moveEnemy();
		}
		else
		{
			int endNode = 1 + (rand() % m_endNodes.size());
			int nodeEnd = m_endNodes[endNode];
			if (m_enemyNode == nodeEnd)
			{
				int endNode = 1 + (rand() % m_endNodes.size());
				nodeEnd = m_endNodes[endNode];
			}
			else
			{
				m_gamePath->newPath(m_enemyNode, nodeEnd);
				m_gamePath->update();
				graphPath = m_gamePath->getGraphPath();
			}

		}
	}
	else
	{
		if (graphPath.empty() == false)
		{
			moveEnemy();
		}
		else
		{
			m_gamePath->newPath(m_enemyNode, m_playerNode);
			m_gamePath->update();
			graphPath = m_gamePath->getGraphPath();
		}
	}
}

void Enemy::enemyFollowPlayer()
{
}
