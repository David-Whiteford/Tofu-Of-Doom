#include "GameWorld.h"

/// <summary>
/// Constructor for the GameWorld class
/// </summary>
GameWorld::GameWorld(sf::RenderWindow &t_window, sf::Time &t_deltaTime, Camera *t_camera) 
	: m_window(t_window), m_deltaTime(t_deltaTime), m_camera(*t_camera)
{
	// Player
	m_player.setRadius(25.0f);
	m_player.setFillColor(sf::Color::Blue);
	m_player.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_player.setPosition(m_camera.getEye().x, m_camera.getEye().z); // Test starting position
	m_newPosition = sf::Vector2f(0, 0);
	m_playerGun.setRadius(5.0f);
	m_playerGun.setFillColor(sf::Color::Red);
	m_playerGun.setOrigin(sf::Vector2f(5, 5));
	m_playerGun.setPosition(m_camera.getEye().x, m_camera.getEye().z + 5); // Test starting position

	m_endNodes.push_back(252);
	m_endNodes.push_back(491);
	m_endNodes.push_back(855);
	m_endNodes.push_back(1955);
	m_endNodes.push_back(1420);
	m_endNodes.push_back(2353);
	m_endNodes.push_back(681);
	m_endNodes.push_back(2237);

	// m_eye = glm::vec3(m_player.getPosition().x, 2.0f, m_player.getPosition().y);
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

	// View
	// m_mapView.setViewport(sf::FloatRect(0.0, 0.0f, 0.25f, 0.25f));
	m_mapView.setSize(m_window.getSize().x, m_window.getSize().y);

	// Create an array to store the walls in (for the pause screen map)
	for (int i = 0; i < m_map->getMap()->size(); ++i)
	{
		if (m_map->getMap()->at(i).second == WallType::WALLTYPE_1)
		{
			sf::RectangleShape f_tempWall;
			f_tempWall.setSize(sf::Vector2f(s_wallWidth, s_wallWidth));
			f_tempWall.setOrigin(s_wallWidth / 2.0f, s_wallWidth / 2.0f);
			f_tempWall.setFillColor(sf::Color::Green);
			f_tempWall.setPosition(m_map->getMap()->at(i).first.x, m_map->getMap()->at(i).first.z);
			m_walls.push_back(f_tempWall);
		}
	}

	//Astar
	m_gamePath->initAStar(m_walls);
	m_gamePath->setPath();
	graphPath = m_gamePath->getGraphPath();

}

/// <summary>
/// Destructor for the GameWorld class
/// </summary>
GameWorld::~GameWorld()
{

}

/// <summary>
/// Update the world
/// </summary>
void GameWorld::updateWorld()
{
	m_player.setPosition(m_camera.getEye().x * s_displayScale, m_camera.getEye().z * s_displayScale);
	setGunPosition();

	/**----------------------------------------------------------------------------------------------------------------*/
	m_playerNode = m_gamePath->nodePos(m_player.getPosition());
	m_enemyNode = m_gamePath->nodePos(m_enemies.front().getPosition());

	sf::Vector2f offSet = sf::Vector2f(150, 150);
	if (m_player.getPosition().x >= m_enemies.front().getPosition().x - offSet.x
		&& m_player.getPosition().x <= m_enemies.front().getPosition().x + offSet.x
		&& m_player.getPosition().y >= m_enemies.front().getPosition().y - offSet.y
		&& m_player.getPosition().y <= m_enemies.front().getPosition().y + offSet.y)
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
	
	/*---------------------------------------------------------------------------------------------------------------------*/

	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isActive())
		{
			bullets[i].update();
			for (int x = 0; x < m_walls.size(); x++)
			{
				if(bullets[i].checkCollision(m_walls.at(x).getPosition(), m_walls.at(x).getSize().x/2))
				{
					if (bullets[i].raycast.isInterpolating())
					{
						bullets[i].raycast.addToHitObjects(&m_walls.at(x));
					}
				}
			}
			for (int x = 0; x < 2; x++)
			{
				if (bullets[i].checkCollision(m_enemies.at(x).getPosition(), m_enemies[x].getRadius()))
				{
					if (bullets[i].raycast.isInterpolating())
					{
						bullets[i].raycast.addToHitObjects(&m_enemies.at(x));
					}
					else
					{
						m_enemies.at(x).setPosition(10, 10);
					}
					bullets[i].setActive(false);
				}
			}
			
		}
		if (bullets[i].canDrawBulletTracer())
		{
			bullets[i].update();
			while (bullets[i].raycast.getHitObjects().size() > 0)
			{
				bullets[i].raycast.getClosest();

			}
		}
	}
}
void GameWorld::enemyFollowPlayer()
{
}
void GameWorld::moveEnemy()
{

	sf::Vector2f graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);
	sf::Vector2f moveTo = m_transform.moveTowards(m_enemies.front().getPosition(), graphPathVec, m_speedEn);
	m_enemies.front().setPosition(moveTo);
	if (m_enemies.front().getPosition().x == graphPath.back()->m_data.m_x &&
		m_enemies.front().getPosition().y == graphPath.back()->m_data.m_y)
	{
		graphPath.pop_back();
	}

	//for (int i = 0; i <  m_enemies.size(); i++)
	//{

	//	sf::Vector2f graphPathVec = sf::Vector2f(graphPath.back()->m_data.m_x, graphPath.back()->m_data.m_y);
	//	sf::Vector2f moveTo = m_transform.moveTowards(m_enemies[i].getPosition(), graphPathVec, m_speedEn);
	//	m_enemies[i].setPosition(moveTo);
	//	if (m_enemies[i].getPosition().x == graphPath.back()->m_data.m_x &&
	//		m_enemies[i].getPosition().y == graphPath.back()->m_data.m_y)
	//	{

	//		graphPath.pop_back();

	//	}
	//}



}
/// <summary>
/// Moves the enemy
/// </summary>
void GameWorld::enemyMovement()
{
	if (follow == false)
	{
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



/// <summary>
/// Draw the world
/// </summary>
void GameWorld::drawWorld()
{
	for (int i = 0; i < m_walls.size(); ++i)
	{
		m_window.draw(m_walls[i]);
	}
	m_mapView.setCenter(m_player.getPosition());
	m_window.setView(m_mapView);
	m_window.draw(m_player);
	m_window.draw(m_playerGun);

	m_window.draw(m_camera.raycastForward.drawRay());
	m_window.draw(m_camera.raycastBehind.drawRay());
	m_window.draw(m_camera.raycastToLeft.drawRay());
	m_window.draw(m_camera.raycastToRight.drawRay());

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_window.draw(m_enemies[i]);
	}
	m_gamePath->draw();


	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isActive())
		{
			m_window.draw(bullets[i].bulletSprite());
		}
		if (bullets[i].canDrawBulletTracer())
		{
			m_window.draw(bullets[i].raycast.drawRay());
		}
	}
}

void GameWorld::fireBullet(int t_gunType)
{
	if (t_gunType == 1 || t_gunType == 3)
	{
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isActive() == false)
			{
				bullets[i].setTimeToLive(400);
				glm::vec3 tempDirection(m_camera.getDirection().x, m_camera.getDirection().y, m_camera.getDirection().z);
				glm::normalize(tempDirection);
				bullets[i].bulletInit(sf::Vector2f(tempDirection.x, tempDirection.z), 0, m_playerGun.getPosition());
				break;
			}
		}
	}
	else if (t_gunType == 2)
	{
		int bulletSpreadAmount = 0;
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i].isActive() == false)
			{
				glm::vec3 tempDirection(m_camera.getDirection().x, m_camera.getDirection().y, m_camera.getDirection().z);

				float offsetX = ((float(rand()) / float(RAND_MAX)) * (0.2f - -0.2f)) + -0.2f;
				float offsetZ = ((float(rand()) / float(RAND_MAX)) * (0.2f - -0.2f)) + -0.2f;

				bullets[i].setTimeToLive(200);

				glm::normalize(tempDirection);

				bullets[i].bulletInit(sf::Vector2f(tempDirection.x + offsetX, tempDirection.z + offsetZ), 0, m_playerGun.getPosition());
				bulletSpreadAmount++;

				if (bulletSpreadAmount > 4)
				{
					break;
				}
			}
		}
	}

}

void GameWorld::checkPlayerRayCollsions()
{
	m_camera.setCanMoveUp(true);
	m_camera.setCanMoveDown(true);
	m_camera.setCanMoveLeft(true);
	m_camera.setCanMoveRight(true);

	for (int x = 0; x < m_walls.size(); x++)
	{
		if (m_camera.canGoUp())
		{
			if (m_camera.raycastForward.hit(m_walls.at(x).getPosition(), m_walls.at(x).getSize().x))
			{
				m_camera.setCanMoveUp(false);
			}
		}
		if (m_camera.canGoDown())
		{
			if (m_camera.raycastBehind.hit(m_walls.at(x).getPosition(), m_walls.at(x).getSize().x))
			{
				m_camera.setCanMoveDown(false);
			}
		}
		if (m_camera.canGoLeft())
		{
			if (m_camera.raycastToLeft.hit(m_walls.at(x).getPosition(), m_walls.at(x).getSize().x))
			{
				m_camera.setCanMoveLeft(false);
			}
		}
		if (m_camera.canGoRight())
		{
			if (m_camera.raycastToRight.hit(m_walls.at(x).getPosition(), m_walls.at(x).getSize().x))
			{
				m_camera.setCanMoveRight(false);
			}
		}

		if (m_camera.canGoLeft() == false && m_camera.canGoDown() == false)
		{
			break;
		}
		if (m_camera.canGoRight() == false && m_camera.canGoDown() == false)
		{
			break;
		}
		
		if (m_camera.canGoLeft() == false && m_camera.canGoUp() == false)
		{
			break;
		}
		if (m_camera.canGoRight() == false && m_camera.canGoUp() == false)
		{
			break;
		}
	}
}

/// <summary>
/// Returns the position of the player's origin
/// </summary>
sf::Vector2f GameWorld::getPlayerPosition()
{
	return m_player.getPosition();
}

/// <summary>
/// Returns the position of enemies
/// </summary>
sf::Vector2f GameWorld::getEnemyPosition()
{
	return m_enemies.front().getPosition() / s_displayScale;
}

/// <summary>
/// Returns the position of the camera
/// </summary>
glm::vec3 GameWorld::getCameraPosition()
{
	return m_eye;
}

/// <summary>
/// Returns the current pitch of the camera
/// </summary>
double GameWorld::getPitch()
{
	return m_pitch;
}

/// <summary>
/// Returns the current yaw of the camera
/// </summary>
double GameWorld::getYaw()
{
	return m_yaw;
}

/// <summary>
/// Returns the wall data from the Map class
/// </summary>
std::vector<std::pair<glm::vec3, WallType>> *GameWorld::getWallData()
{
	return m_map->getMap();
}

/// <summary>
/// Gets the light positions from the GameWorld map
/// </summary>
std::vector<glm::vec3> *GameWorld::getLightPositions()
{
	return m_map->getLightPositions();
}

void GameWorld::setGunPosition()
{
	glm::vec3 tempDirection(m_camera.getDirection().x, m_camera.getDirection().y, m_camera.getDirection().z);
	glm::normalize(tempDirection);
	glm::vec3 offsetPos = tempDirection * -2.0f;

	sf::Vector2f position = sf::Vector2f((offsetPos.x + m_camera.transform.position.x) * s_displayScale,
		(offsetPos.z + m_camera.transform.position.z) * s_displayScale);

	// gun position equals z + 5 normalised 

	m_playerGun.setPosition(sf::Vector2f(position.x, position.y));
}

