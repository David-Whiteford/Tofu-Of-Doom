#include "GameWorld.h"

/// <summary>
/// Constructor for the GameWorld class
/// </summary>
GameWorld::GameWorld(sf::RenderWindow& t_window, sf::Time& t_deltaTime, Camera* t_camera)
	: m_window(t_window), m_deltaTime(t_deltaTime), m_camera(*t_camera)
{
	// Player
	m_player.setPosition(m_camera.getEye().x, m_camera.getEye().z); // Test starting position
	m_newPosition = sf::Vector2f(0, 0);
	m_playerGun.setRadius(5.0f);
	m_playerGun.setFillColor(sf::Color::Red);
	m_playerGun.setOrigin(sf::Vector2f(5, 5));
	m_playerGun.setPosition(m_camera.getEye().x, m_camera.getEye().z + 5); // Test starting position

	// Vector of endNodes
	m_endNodes.push_back(252);
	m_endNodes.push_back(491);
	m_endNodes.push_back(855);
	m_endNodes.push_back(1955);
	m_endNodes.push_back(1420);
	m_endNodes.push_back(2353);
	m_endNodes.push_back(681);
	m_endNodes.push_back(2237);

	// Enemy position start
	m_startingPos.push_back(sf::Vector2f(1557, 260));
	m_startingPos.push_back(sf::Vector2f(2364, 436));
	m_startingPos.push_back(sf::Vector2f(375, 861));
	m_startingPos.push_back(sf::Vector2f(71, 439));
	m_startingPos.push_back(sf::Vector2f(72, 2121));
	m_startingPos.push_back(sf::Vector2f(1577, 824));
	m_startingPos.push_back(sf::Vector2f(1518, 1365));
	m_startingPos.push_back(sf::Vector2f(2313, 2356));
	m_startingPos.push_back(sf::Vector2f(1557, 260));
	m_startingPos.push_back(sf::Vector2f(2364, 436));
	m_startingPos.push_back(sf::Vector2f(375, 861));
	m_startingPos.push_back(sf::Vector2f(71, 439));
	m_startingPos.push_back(sf::Vector2f(72, 2121));
	m_startingPos.push_back(sf::Vector2f(1577, 824));
	m_startingPos.push_back(sf::Vector2f(1518, 1365));
	m_startingPos.push_back(sf::Vector2f(2313, 2356));
	m_startingPos.push_back(sf::Vector2f(1557, 260));
	m_startingPos.push_back(sf::Vector2f(2364, 436));
	m_startingPos.push_back(sf::Vector2f(375, 861));
	m_startingPos.push_back(sf::Vector2f(71, 439));
	m_startingPos.push_back(sf::Vector2f(72, 2121));
	m_startingPos.push_back(sf::Vector2f(1577, 824));
	m_startingPos.push_back(sf::Vector2f(1518, 1365));
	m_startingPos.push_back(sf::Vector2f(2313, 2356));

	for (int i = 0; i < 18; i++)
	{
		m_enemyVec[i] = new Enemy(m_window, m_deltaTime, m_startingPos[i], m_gamePath);
		m_enemyVec[i]->setAlive(true);

		// Add enemy to the active vector
		m_enemyActive.push_back(m_enemyVec[i]);
	}

	// View
	// m_mapView.setViewport(sf::FloatRect(0.0, 0.0f, 0.25f, 0.25f));
	m_mapView.setSize(m_window.getSize().x, m_window.getSize().y);

	int wallIndex = 0;
	quadtree.clear();

	// Create an array to store the walls in (for the pause screen map)
	for (int i = 0; i < m_map->getMap()->size(); ++i)
	{
		if (m_map->getMap()->at(i).second == WallType::WALLTYPE_1)
		{
			m_wallVec.push_back(new Wall(m_window, s_wallWidth, sf::Vector2f(m_map->getMap()->at(i).first.x, m_map->getMap()->at(i).first.z)));

			GameObject* wall = dynamic_cast<GameObject*>(m_wallVec.back());
			wall->size = s_wallWidth;
			wall->position = m_wallVec.back()->getShape().getPosition();

			quadtree.addObject(wall);
		}
	}

	// A*
	m_gamePath->initAStar(m_wallVec);

	for (int i = 0; i < 8; i++)
	{
		m_enemyVec[i] = new Enemy(m_window, m_deltaTime, m_startingPos[i], m_gamePath);
		m_enemyVec[i]->setAlive(true);

		// Add enemy to the active vector
		m_enemyActive.push_back(m_enemyVec[i]);
	}

	for (int i = 0; i < 100; i++)
	{
		bullets[i] = new Bullet();
	}
}

/// <summary>
/// Destructor for the GameWorld class
/// </summary>
GameWorld::~GameWorld()
{
	delete m_gamePath;
	delete m_map;
}

/// <summary>
/// Update the world
/// </summary>
void GameWorld::updateWorld()
{	
	m_player.setPosition(m_camera.getEye().x * s_displayScale, m_camera.getEye().z * s_displayScale);
	m_player.update();
	setGunPosition();
	updateBulletPhysics();

	// Only update the active enemies
	for (int i = 0; i < m_enemyActive.size(); i++)
	{
		m_enemyActive[i]->update(m_player.getSprite());
	}

	// Check and remove objects
	checkEnemyInQueueAlive();
}

/// <summary>
/// Draw the world
/// </summary>
void GameWorld::drawWorld()
{
	m_mapView.setCenter(m_player.getPosition());
	m_window.setView(m_mapView);

	for (int i = 0; i < m_enemyActive.size(); i++)
	{
		m_window.draw(m_enemyActive[i]->getSprite());
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

	m_window.draw(m_player.getSprite());
	m_window.draw(m_playerGun);
	m_window.draw(m_camera.raycastForward.drawRay());
	m_window.draw(m_camera.raycastBehind.drawRay());
	m_window.draw(m_camera.raycastToLeft.drawRay());
	m_window.draw(m_camera.raycastToRight.drawRay());
	quadtreeBullet.draw(m_window, returnWall);

	for (int i = 0; i < activeBullets.size(); i++)
	{
		if (activeBullets[i]->canDrawBulletTracer())
		{
			m_window.draw(activeBullets[i]->raycast.drawRay());
			activeBullets[i]->update();
		}
	}
}

void GameWorld::drawUI()
{
	ui_view.setCenter(sf::Vector2f(0,0));

	m_window.draw(ui.getText());

	if (m_camera.controller.leftButton())
	{
		ui.x--;
	}
	else if (m_camera.controller.rightButton())
	{

		ui.x++;
	}

	if (m_camera.controller.leftButtonRTS())
	{
		ui.y--;
	}
	else if (m_camera.controller.rightButtonRTS())
	{

		ui.y++;
	}

	std::cout << "x: " + std::to_string(ui.x) << ", y: " + std::to_string(ui.y) << std::endl;
	std::cout << "px: " + std::to_string(getPlayerPosition().x) << ", py: " + std::to_string(getPlayerPosition().y) << std::endl;

	ui.update();

}

void GameWorld::fireBullet(int t_gunType)
{
	for (int i = 0; i < m_wallVec.size(); i++)
	{
		quadtreeBullet.addObject(m_wallVec[i]);
	}

	if (t_gunType == 1 || t_gunType == 3)
	{
		for (int i = 0; i < 100; i++)
		{
			if (bullets[i]->isActive() == false)
			{
				glm::vec3 tempDirection(m_camera.getDirection().x, m_camera.getDirection().y, m_camera.getDirection().z);
				glm::normalize(tempDirection);
				bullets[i]->bulletInit(sf::Vector2f(tempDirection.x, tempDirection.z), 0, m_playerGun.getPosition());
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
			if (bullets[i]->isActive() == false)
			{
				glm::vec3 tempDirection(m_camera.getDirection().x, m_camera.getDirection().y, m_camera.getDirection().z);

				float offsetX = ((float(rand()) / float(RAND_MAX)) * (0.2f - -0.2f)) + -0.2f;
				float offsetZ = ((float(rand()) / float(RAND_MAX)) * (0.2f - -0.2f)) + -0.2f;

				glm::normalize(tempDirection);

				bullets[i]->bulletInit(sf::Vector2f(tempDirection.x + offsetX, tempDirection.z + offsetZ), 0, m_playerGun.getPosition());
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

/// <summary>
/// Update the bullet physics
/// </summary>
void GameWorld::updateBulletPhysics()
{
	// Check bullet physics
	for (int i = 0; i < activeBullets.size(); i++)
	{
		// Clear previous list
		previousReturn.clear();

		while (activeBullets[i]->isActive() && activeBullets[i]->getSteps() < activeBullets[i]->getMaxStepCount())
		{
			activeBullets[i]->update();
			returnWall = quadtreeBullet.getObjectsAt(activeBullets[i]->getPosition().x, activeBullets[i]->getPosition().y, 8);
			std::cout << "returnWall Count: " << std::to_string(returnWall.size()) << std::endl; // TODO: Delete this

			for (int x = 0; x < previousReturn.size(); x++)
			{
				if (activeBullets[i]->checkCollision(previousReturn.at(x)->position, previousReturn.at(x)->size / 2))
				{
					if (activeBullets[i]->raycast.isInterpolating())
					{
						activeBullets[i]->raycast.addToHitObjects(previousReturn.at(x));
						activeBullets[i]->setActive(false);

						break;
					}

					std::cout << "previous hit" << std::endl; // TODO: Delete this
				}
			}

			// Nothing on previous then check next
			if (activeBullets[i]->isActive())
			{
				for (int x = 0; x < returnWall.size(); x++)
				{
					if (activeBullets[i]->checkCollision(returnWall.at(x)->position, returnWall.at(x)->size / 2))
					{
						if (activeBullets[i]->raycast.isInterpolating())
						{
							activeBullets[i]->raycast.addToHitObjects(returnWall.at(x));
							activeBullets[i]->setActive(false);
							break;
						}
					}
				}
			}
			for (int x = 0; x < m_enemyActive.size(); x++)
			{
				if (activeBullets[i]->checkCollision(m_enemyActive[x]->getPosition(), m_enemyActive[x]->getRadius()))
				{
					if (activeBullets[i]->raycast.isInterpolating())
					{
						activeBullets[i]->raycast.addToHitObjects(m_enemyActive.at(x));
					}
					else
					{
						m_enemyActive.at(x)->setAlive(false);
					}
				}
			}

			// Set to previous for checks
			previousReturn = returnWall;
			returnWall.clear();

			if (activeBullets[i]->isActive() == false)
			{
				break;
			}
	
		}
		
		while (activeBullets[i]->raycast.getHitObjects().size() > 0)
		{
			if (activeBullets[i]->raycast.getClosest()->getTag() == ENEMY_TAG)
			{
				dynamic_cast<Enemy*>(activeBullets[i]->raycast.getClosest())->setDead();
			}
		}

	}

	std::vector<Bullet*> newBulletList;

	// Tracer one frame rule has passed so we remove from the list
	for (int i = 0; i < activeBullets.size(); i++)
	{
		if (activeBullets[i]->isActive() == true)
		{
			newBulletList.push_back(activeBullets[i]);
		}
		else
		{
			activeBullets[i]->setStepCount(0);
			activeBullets[i]->setActive(false);
		}

		if (i + 1 == activeBullets.size())
		{
			activeBullets.clear();
			activeBullets = newBulletList;
			newBulletList.clear();
		}
	}

	quadtreeBullet.clear();
}

/// <summary>
/// Check player collisions
/// </summary>
void GameWorld::checkPlayerRayCollsions(sf::Time t_deltaTime)
{

	m_camera.setCanMoveUp(true);
	m_camera.setCanMoveDown(true);
	m_camera.setCanMoveLeft(true);
	m_camera.setCanMoveRight(true);

	std::vector<GameObject*> returnObjectsTop = quadtree.getObjectsAt(m_camera.raycastForward.getEndPoint().x, m_camera.raycastForward.getEndPoint().y, 0);
	std::vector<GameObject*> returnObjectsBack = quadtree.getObjectsAt(m_camera.raycastBehind.getEndPoint().x, m_camera.raycastBehind.getEndPoint().y, 0);
	std::vector<GameObject*> returnObjectsLeft = quadtree.getObjectsAt(m_camera.raycastToLeft.getEndPoint().x, m_camera.raycastToLeft.getEndPoint().y, 0);
	std::vector<GameObject*> returnObjectsRight = quadtree.getObjectsAt(m_camera.raycastToRight.getEndPoint().x, m_camera.raycastToRight.getEndPoint().y, 0);
	
	// Check ray collisions
	for (int x = 0; x < returnObjectsTop.size(); x++)
	{
		if (m_camera.canGoUp())
		{
			if (m_camera.raycastForward.hit(returnObjectsTop[x]->position, returnObjectsTop[x]->size))
			{
				m_camera.setCanMoveUp(false);
				break;
			}
		}
	}

	for (int x = 0; x < returnObjectsBack.size(); x++)
	{
		if (m_camera.canGoDown())
		{
			if (m_camera.raycastBehind.hit(returnObjectsBack[x]->position, returnObjectsBack[x]->size))
			{
				m_camera.setCanMoveDown(false);
				break;
			}
		}
	}

	for (int x = 0; x < returnObjectsLeft.size(); x++)
	{
		if (m_camera.canGoLeft())
		{
			if (m_camera.raycastToLeft.hit(returnObjectsLeft[x]->position, returnObjectsLeft[x]->size))
			{
				m_camera.setCanMoveLeft(false);
				break;
			}
		}
	}

	for (int x = 0; x < returnObjectsRight.size(); x++)
	{
		if (m_camera.canGoRight())
		{
			if (m_camera.raycastToRight.hit(returnObjectsRight[x]->position, returnObjectsRight[x]->size))
			{
				m_camera.setCanMoveRight(false);
				break;
			}
		}
	}

	if ((!m_camera.canGoUp()) && (m_camera.canGoLeft() || m_camera.canGoRight()))
	{
		m_camera.getOutOfWall(t_deltaTime);
	}

	if (!m_camera.canGoUp() && !m_camera.canGoRight() && !m_camera.canGoLeft() && !m_camera.canGoDown())
	{
		m_camera.popOutFromWall();
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
/// Get the enemy position of an enemy at a specifed index value
/// </summary>
sf::Vector2f GameWorld::getEnemyPosition(int index)
{
	if (m_enemyActive.size() > 0)
	{
		return m_enemyActive.at(index)->getSprite().getPosition();
	}
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
std::vector<std::pair<glm::vec3, WallType>>* GameWorld::getWallData()
{
	return m_map->getMap();
}

/// <summary>
/// Gets the light positions from the GameWorld map
/// </summary>
std::vector<glm::vec3>* GameWorld::getLightPositions()
{
	return m_map->getLightPositions();
}

/// <summary>
/// Gets the fire extinguisher positions from the GameWorld map
/// </summary>
std::vector<glm::vec3>* GameWorld::getFireExtPositions()
{
	return m_map->getFireExtPositions();
}

/// <summary>
/// Gets the oil drum positions from the GameWorld map
/// </summary>
std::vector<glm::vec3>* GameWorld::getOilDrumPositions()
{
	return m_map->getOilDrumPositions();
}

/// <summary>
/// Gets the chair positions from the GameWorld map
/// </summary>
std::vector<glm::vec3>* GameWorld::getChairPositions()
{
	return m_map->getChairPositions();
}

/// <summary>
/// Gets the table (type 1) positions from the GameWorld map
/// </summary>
std::vector<glm::vec3>* GameWorld::getTable1Positions()
{
	return m_map->getTable1Positions();
}

/// <summary>
/// Gets the table (type 2) positions from the GameWorld map
/// </summary>
std::vector<glm::vec3>* GameWorld::getTable2Positions()
{
	return m_map->getTable2Positions();
}

/// <summary>
/// Gets the amount of enemies currently active
/// </summary>
int GameWorld::getActiveEnemyCount()
{
	return m_enemyActive.size();
}

/// <summary>
/// Check which enemies in the queue are alive
/// </summary>
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

		// We made it to the end so lets get out of this loop 
		if (!removedEnemy)
		{
			reachedEnd = true;
		}
	}
}

/// <summary>
/// Populate quad tree
/// </summary>
void GameWorld::populateQuadtree()
{
	for (int i = 0; i < m_wallVec.size(); i++)
	{

		quadtree.addObject(m_wallVec.at(i)->myGameObject);
		quadtreeBullet.addObject(m_wallVec.at(i)->myGameObject);
	}
}

/// <summary>
/// Set gun position
/// </summary>
void GameWorld::setGunPosition()
{
	glm::vec3 tempDirection(m_camera.getDirection().x, m_camera.getDirection().y, m_camera.getDirection().z);
	glm::normalize(tempDirection);
	glm::vec3 offsetPos = tempDirection * -2.0f;
	sf::Vector2f position = sf::Vector2f((offsetPos.x + m_camera.transform.position.x) * s_displayScale, (offsetPos.z + m_camera.transform.position.z) * s_displayScale);
	m_playerGun.setPosition(sf::Vector2f(position.x, position.y));
}
