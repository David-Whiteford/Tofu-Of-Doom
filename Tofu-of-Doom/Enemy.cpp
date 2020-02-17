#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow& t_window, sf::Time& t_deltaTime,sf::Vector2f t_position, Path* t_gamePath)
	: m_window(t_window), m_deltaTime(t_deltaTime), 
	m_position(t_position),m_enemyBehaviour(EnemyBehaviour::PATROL_MAP), 
	m_gamePath(t_gamePath)
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
	delete(m_gamePath);
	delete(this);
}

void Enemy::enemyInit()
{
	myGameObject = dynamic_cast<GameObject*>(this);
	float startSize = 0.5f;
	float currentSize = 0.5f;

	float reduceSpeed = 0.01f;
	bool canRender = true;
	m_enemy.setRadius(m_radius);
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_enemy.setPosition(100, 800); // Test starting position
	//get initial enemy Position
	m_enemyNode = m_gamePath->nodePos(m_enemy.getPosition());
	//Astar
	int nodeEnd = getRandNode();
	m_gamePath->newPath(m_enemyNode, nodeEnd);

	setSpeed(25);


	dynamic_cast<GameObject*>(this)->setTag(ENEMY_TAG);
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
	if (m_alive)
	{
		//sets the node the player and the enemy are in
		m_playerNode = m_gamePath->nodePos(t_player.getPosition());
		m_enemyNode = m_gamePath->nodePos(m_enemy.getPosition());
		myGameObject->position = m_enemy.getPosition();

		sf::Vector2f offSet = sf::Vector2f(300, 300);
		if (t_player.getPosition().x >= m_enemy.getPosition().x - offSet.x
			&& t_player.getPosition().x <= m_enemy.getPosition().x + offSet.x
			&& t_player.getPosition().y >= m_enemy.getPosition().y - offSet.y
			&& t_player.getPosition().y <= m_enemy.getPosition().y + offSet.y)
		{

			if (m_doOnceSeek != 1)
			{
				m_enemyBehaviour = EnemyBehaviour::SEEK_PLAYER;
				m_doOnceSeek++;
				graphPath.resize(0);
				m_doOncePatrol = 0;
			}
		}
		else
		{
			if (m_doOncePatrol != 1)
			{
				m_enemyBehaviour = EnemyBehaviour::PATROL_MAP;
				m_doOncePatrol++;
				graphPath.resize(0);
				m_doOnceSeek = 0;
			}
		}
		enemyMovement();
	}
	else if(canRender)
	{
		if (currentSize > 0)
		{
			currentSize -= reduceSpeed;
		}
		else
		{
			canRender = false;
		}
	}
}

void Enemy::draw()
{
	m_window.draw(m_enemy);

}
void Enemy::moveEnemy()
{
	graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);

	sf::Vector2f moveTo = m_transform.moveTowards(m_enemy.getPosition(), graphPathVec, m_speedEn);
	m_enemy.setPosition(moveTo);
	if (m_enemy.getPosition().x == graphPath.back()->m_data.m_x &&
		m_enemy.getPosition().y == graphPath.back()->m_data.m_y)
	{
		graphPath.pop_back();
	}

}
/// <summary>
/// Moves the enemy
/// </summary>
void Enemy::enemyMovement()
{
	switch (m_enemyBehaviour)
	{
		case EnemyBehaviour::SEEK_PLAYER:
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
			break;
		case EnemyBehaviour::STOP:
			break;
		case EnemyBehaviour::PATROL_MAP:
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
			break;
		default:
			break;
	}
}

void Enemy::enemyFollowPlayer()
{
}
float Enemy::getRadius()
{
	return m_radius;
}
sf::CircleShape Enemy::getSprite()
{
	return m_enemy;
}
int Enemy::getRandNode()
{
	int endNode = rand() % 7;
	int nodeEnd = m_endNodes[endNode];
	if (m_enemyNode == nodeEnd)
	{
		int endNode = rand() %7;
		nodeEnd = m_endNodes[endNode];
	}
	return nodeEnd;
}

sf::Vector2f Enemy::getPosition()
{
	return m_enemy.getPosition();
}

void Enemy::setAlive(bool t_alive)
{
	m_alive = t_alive;
}

void Enemy::setDead()
{
	this->m_alive = false;
}

bool Enemy::isAlive()
{
	return m_alive;
}
