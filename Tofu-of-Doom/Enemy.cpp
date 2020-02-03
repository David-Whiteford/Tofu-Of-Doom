#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow& t_window, sf::Time& t_deltaTime,sf::Vector2f t_position, std::vector<sf::RectangleShape> t_walls)
	: m_window(t_window), m_deltaTime(t_deltaTime), m_position(t_position),m_walls(t_walls)
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
	
	m_enemies.setRadius(25.0f);
	m_enemies.setFillColor(sf::Color::Red);
	m_enemies.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_enemies.setPosition(100, 800); // Test starting position
	//get initial enemy Position
	m_enemyNode = m_gamePath->nodePos(m_enemies.getPosition());
	//Astar
	m_gamePath->initAStar(m_walls);
	int nodeEnd = getRandNode();
	m_gamePath->newPath(m_enemyNode, nodeEnd);
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
	m_position = t_pos;
}

void Enemy::update(sf::CircleShape t_player)
{
	//sets the node the player and the enemy are in
	m_playerNode = m_gamePath->nodePos(t_player.getPosition());
	m_enemyNode = m_gamePath->nodePos(m_enemies.getPosition());

	sf::Vector2f offSet = sf::Vector2f(150, 150);
	if (t_player.getPosition().x >= m_enemies.getPosition().x - offSet.x
		&& t_player.getPosition().x <= m_enemies.getPosition().x + offSet.x
		&& t_player.getPosition().y >= m_enemies.getPosition().y - offSet.y
		&& t_player.getPosition().y <= m_enemies.getPosition().y + offSet.y)
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
	m_window.draw(m_enemies);
}
void Enemy::moveEnemy()
{
	sf::Vector2f graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);
	sf::Vector2f moveTo = m_transform.moveTowards(m_enemies.getPosition(), graphPathVec, m_speedEn);
	m_enemies.setPosition(moveTo);
	if (m_enemies.getPosition().x == graphPath.back()->m_data.m_x &&
		m_enemies.getPosition().y == graphPath.back()->m_data.m_y)
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
		if (graphPath.empty() == false)
		{
			moveEnemy();
		}
		else
		{
			int nodeEnd = getRandNode();
			m_gamePath->newPath(m_enemyNode, nodeEnd);
			m_gamePath->update();
			graphPath = m_gamePath->getGraphPath();
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
int Enemy::getRandNode()
{
	int endNode = 1 + (rand() % m_endNodes.size());
	int nodeEnd = m_endNodes[endNode];
	if (m_enemyNode == nodeEnd)
	{
		int endNode = 1 + (rand() % m_endNodes.size());
		nodeEnd = m_endNodes[endNode];
	}
	return nodeEnd;
}
