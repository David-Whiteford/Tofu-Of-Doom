#include "Boss.h"

Boss::Boss(sf::RenderWindow& t_window, sf::Time& t_deltaTime, sf::Vector2f t_position, Path* t_gamePath)
	: m_window(t_window), m_deltaTime(t_deltaTime),
	m_position(t_position), m_enemyBehaviour(EnemyBehaviour::STOP),
	m_gamePath(t_gamePath)
{

	setUpBoss();
}

Boss::~Boss()
{
}

void Boss::update(sf::Time t_deltaTime , sf::CircleShape t_player)
{
	
	m_playerNode = m_gamePath->nodePos(t_player.getPosition());
	m_enemyNode = m_gamePath->nodePos(m_bossCircle.getPosition());

	std::cout << "playerNode: " << m_playerNode << std::endl;
	sf::Vector2f offSet = sf::Vector2f(300, 300);
	if (t_player.getPosition().x >= m_bossCircle.getPosition().x - offSet.x
		&& t_player.getPosition().x <= m_bossCircle.getPosition().x + offSet.x
		&& t_player.getPosition().y >= m_bossCircle.getPosition().y - offSet.y
		&& t_player.getPosition().y <= m_bossCircle.getPosition().y + offSet.y)
	{
		if (m_doOnceSeek != 1)
		{
			m_enemyBehaviour = EnemyBehaviour::SEEK_PLAYER;
			m_doOnceSeek = 1;
			graphPath.resize(0);
			m_doOncePatrol = 0;
		}
	}
	else
	{
		if (m_doOncePatrol != 1)
		{
			m_enemyBehaviour = EnemyBehaviour::STOP;
			m_doOncePatrol = 1;
			graphPath.resize(0);
			m_doOnceSeek = 0;
		}
	}
	enemyMovement(t_deltaTime);
}

void Boss::enemyMovement(sf::Time t_deltaTime)
{
	switch (m_enemyBehaviour)
	{
	case EnemyBehaviour::SEEK_PLAYER:
		if (graphPath.empty() == false)
		{
			moveEnemy(t_deltaTime);
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
	case EnemyBehaviour::PATROL:
		break;
	default:
		break;
	}
}
void Boss::moveEnemy(sf::Time t_deltaTime)
{
	graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);
	
	sf::Vector2f moveTo = m_transform.moveTowards(m_bossCircle.getPosition(), graphPathVec, m_speedEn * t_deltaTime.asMilliseconds());
	m_bossCircle.setPosition(moveTo);
	if (m_bossCircle.getPosition().x == graphPath.back()->m_data.m_x &&
		m_bossCircle.getPosition().y == graphPath.back()->m_data.m_y)
	{
		graphPath.pop_back();
	}

}
void Boss::setHealth(int t_healthAmount)
{
	m_health = t_healthAmount;
}

int Boss::getHealth()
{
	return m_health;
}

void Boss::setUpBoss()
{
	m_bossCircle.setRadius(m_radius);
	m_bossCircle.setFillColor(sf::Color::Green);
	m_bossCircle.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_bossCircle.setPosition(m_position); // Test starting position
}

void Boss::render()
{
	m_window.draw(m_bossCircle);
}

void Boss::decreaseHealth(int t_healthAmount)
{
	m_health -= t_healthAmount;

	if (m_health < 0)
	{
		m_health = 0;
	}
}

float Boss::getRadius()
{
	return m_radius;
}
sf::CircleShape Boss::getSprite()
{
	return m_bossCircle;
}
int Boss::getRandNode()
{
	int endNode = rand() % 7;
	int nodeEnd = m_endNodes[endNode];
	if (m_enemyNode == nodeEnd)
	{
		int endNode = rand() % 7;
		nodeEnd = m_endNodes[endNode];
	}
	return nodeEnd;
}

sf::Vector2f Boss::getPosition()
{
	return m_bossCircle.getPosition();
}

void Boss::setAlive(bool t_alive)
{
	m_alive = t_alive;
}

void Boss::setDead()
{
	this->m_alive = false;
}

bool Boss::isAlive()
{
	return m_alive;
}