#include "GameWorld.h"

/// <summary>
/// Constructor for the GameWorld class
/// </summary>
GameWorld::GameWorld(sf::RenderWindow &t_window, sf::Time &t_deltaTime, Camera *t_camera) 
	: m_window(t_window), m_deltaTime(t_deltaTime), m_camera(*t_camera)
{

	//quadtree = new Quadtree(-50, -50, 400, 400, 0, 8);

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

	//vector of endNodes
	m_endNodes.push_back(252);
	m_endNodes.push_back(491);
	m_endNodes.push_back(855);
	m_endNodes.push_back(1955);
	m_endNodes.push_back(1420);
	m_endNodes.push_back(2353);
	m_endNodes.push_back(681);
	m_endNodes.push_back(2237);

	// Enemy position start
	m_startingPos.push_back(sf::Vector2f(1557,260));
	m_startingPos.push_back(sf::Vector2f(2364, 436));
	m_startingPos.push_back(sf::Vector2f(375, 861));
	m_startingPos.push_back(sf::Vector2f(71, 439));
	m_startingPos.push_back(sf::Vector2f(72, 2121));
	m_startingPos.push_back(sf::Vector2f(1577, 824));
	m_startingPos.push_back(sf::Vector2f(1518, 1365));
	m_startingPos.push_back(sf::Vector2f(2313, 2356));
	

	m_enemies.push_back(m_enemy);
	m_enemies.push_back(m_enemy);	
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].setRadius(25.0f);
		m_enemies[i].setFillColor(sf::Color::Red);
		m_enemies[i].setOrigin(sf::Vector2f(25.0f, 25.0f));
		m_enemies[i].setPosition(100, 800); // Test starting position
	}




	// View
	// m_mapView.setViewport(sf::FloatRect(0.0, 0.0f, 0.25f, 0.25f));
	m_mapView.setSize(m_window.getSize().x, m_window.getSize().y);

	int wallIndex = 0;
	quadtree->clear();
	// Create an array to store the walls in (for the pause screen map)
	for (int i = 0; i < m_map->getMap()->size(); ++i)
	{
		if (m_map->getMap()->at(i).second == WallType::WALLTYPE_1)
		{

			m_wallVec.push_back(new Wall(m_window, s_wallWidth, sf::Vector2f(m_map->getMap()->at(i).first.x, m_map->getMap()->at(i).first.z)));
			//sf::RectangleShape f_tempWall;

			GameObject* wall = dynamic_cast<GameObject*>(m_wallVec.back());
			wall->size = s_wallWidth;
			wall->position = m_wallVec.back()->getShape().getPosition();
			
			quadtree->addObject(wall);


		}
	}
	
	// Astar
	m_gamePath->initAStar(m_wallVec);
	



	for (int i = 0; i < 8; i++)
	{

		m_enemyVec[i] =  new Enemy(m_window, m_deltaTime, m_startingPos[i], m_gamePath);
		m_enemyVec[i]->setAlive(true);

		// add enemy to the active vector
		m_enemyActive.push_back(m_enemyVec[i]);
	}
	
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
	for (int i = 0; i < activeBullets.size(); i++)
	{
		
		activeBullets[i].update();
			/*for (int x = 0; x < m_walls.size(); x++)
			{
				if(bullets[i].checkCollision(m_walls.at(x).getPosition(), m_walls.at(x).getSize().x/2))
				{
					if (bullets[i].raycast.isInterpolating())
					{
						bullets[i].raycast.addToHitObjects(m_walls.at(x));
					}
				}
			}*/
		for (int x = 0; x < m_enemyActive.size(); x++)
		{
			if (activeBullets[i].checkCollision(m_enemyActive[x]->getPosition(), m_enemyActive[x]->getRadius()))
			{
				if (activeBullets[i].raycast.isInterpolating())
				{

					activeBullets[i].raycast.addToHitObjects(m_enemyActive.at(x));
				}
				else
				{
					m_enemyActive.at(x)->setAlive(false);
				}
				activeBullets[i].setActive(false);
			}
		}
			
		
		// Tis is the debug line we check for collsion
		if (activeBullets[i].canDrawBulletTracer())
		{
			activeBullets[i].update();
			while (activeBullets[i].raycast.getHitObjects().size() > 0)
			{
				dynamic_cast<Enemy*>(activeBullets[i].raycast.getClosest())->setDead();

			}
		}
	}

	for (int i = 0; i < activeBullets.size(); i++)
	{
		if (activeBullets[i].canDrawBulletTracer() == false)
		{
			activeBullets.erase(activeBullets.begin() + i);
			--i;
		}
	}

	// only update the active enemies
	for (int i = 0; i < m_enemyActive.size(); i++)
	{
		m_enemyActive[i]->update(m_player);
	}

	// check and remove objects
	checkEnemyInQueueAlive();
	//m_enemyObject->update(m_player);

	//quadtree->clear();
}

/// <summary>
/// Draw the world
/// </summary>
void GameWorld::drawWorld()
{

	m_mapView.setCenter(m_player.getPosition());
	m_window.setView(m_mapView);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_window.draw(m_enemies[i]);
	}
	
	for (int i = 0; i < m_wallVec.size(); ++i)
	{
		m_wallVec[i]->draw();
	}
	m_gamePath->draw(m_mapView);

	for (int i = 0; i < m_enemyActive.size(); i++)
	{
		m_enemyActive[i]->draw();
	}

	
	m_window.draw(m_player);
	m_window.draw(m_playerGun);

	std::vector<GameObject*> returnObjects = quadtree->getObjectsAt(getPlayerPosition().x, getPlayerPosition().y);
	quadtree->draw(m_window, returnObjects);

	m_window.draw(m_camera.raycastForward.drawRay());
	m_window.draw(m_camera.raycastBehind.drawRay());
	m_window.draw(m_camera.raycastToLeft.drawRay());
	m_window.draw(m_camera.raycastToRight.drawRay());

	for (int i = 0; i < activeBullets.size(); i++)
	{
		
		if (activeBullets[i].canDrawBulletTracer())
		{
			m_window.draw(activeBullets[i].raycast.drawRay());
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
				activeBullets.push_back(bullets[i]);
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
				activeBullets.push_back(bullets[i]);


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

	std::vector<GameObject*> returnObjects = quadtree->getObjectsAt(getPlayerPosition().x, getPlayerPosition().y);
	std::cout << "number of objects: " << returnObjects.size() << std::endl; 
	std::cout << "number of objects vec: " << m_wallVec.size() << std::endl;
	

	for (int x = 0; x < returnObjects.size(); x++)
	{
		Wall* wall = dynamic_cast<Wall*>(returnObjects[x]);
		if (m_camera.canGoUp())
		{
			if (m_camera.raycastForward.hit(wall->getShape().getPosition(), wall->getShape().getSize().x))
			{
				m_camera.setCanMoveUp(false);
			}
		}
		if (m_camera.canGoDown())
		{
			if (m_camera.raycastBehind.hit(wall->getShape().getPosition(), wall->getShape().getSize().x))
			{
				m_camera.setCanMoveDown(false);
			}
		}
		if (m_camera.canGoLeft())
		{
			if (m_camera.raycastToLeft.hit(wall->getShape().getPosition(), wall->getShape().getSize().x))
			{
				m_camera.setCanMoveLeft(false);
			}
		}
		if (m_camera.canGoRight())
		{
			if (m_camera.raycastToRight.hit(wall->getShape().getPosition(), wall->getShape().getSize().x))
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

void GameWorld::checkEnemyInQueueAlive()
{

	bool reachedEnd = false;
	while (!reachedEnd)
	{
		bool removedEnemy = false;
		for (int i = 0; i < m_enemyActive.size(); i++)
		{
			if (m_enemyActive[i]->isAlive() == false)
			{
				m_enemyActive.erase(m_enemyActive.begin() + i);
				removedEnemy = true;
				break;
			}
		}

		// we made it to the end so lets get out of this loop 
		if (!removedEnemy)
		{
			reachedEnd = true;
		}
	}
	
}

void GameWorld::populateQuadtree()
{
	for (int i = 0; i < m_wallVec.size(); i++)
	{

		quadtree->addObject(m_wallVec.at(i)->myGameObject);
	}
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

