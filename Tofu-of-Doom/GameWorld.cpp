
#include "GameWorld.h"

/// <summary>
/// Constructor for the GameWorld class
/// </summary>
GameWorld::GameWorld(sf::RenderWindow &t_window, sf::Time &t_deltaTime, Camera &t_camera) 
	: m_window(t_window), m_deltaTime(t_deltaTime), m_camera(t_camera)
{
	// Player
	m_player.setRadius(25.0f);
	m_player.setFillColor(sf::Color::Blue);
	m_player.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_player.setPosition(m_camera.getEye().x, m_camera.getEye().z); // Test starting position

	m_playerGun.setRadius(5.0f);
	m_playerGun.setFillColor(sf::Color::Red);
	m_playerGun.setOrigin(sf::Vector2f(5, 5));
	m_playerGun.setPosition(m_camera.getEye().x, m_camera.getEye().z + 5); // Test starting position


	// m_eye = glm::vec3(m_player.getPosition().x, 2.0f, m_player.getPosition().y);
	m_enemies.push_back(m_enemy);
	m_enemies.push_back(m_enemy);	
	
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].setRadius(25.0f);
		m_enemies[i].setFillColor(sf::Color::Red);
		m_enemies[i].setOrigin(sf::Vector2f(25.0f, 25.0f));
		m_enemies[i].setPosition(100, 100); // Test starting position
	}

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

	enemyMove();

	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isActive())
		{
			bullets[i].update();

			for (int x = 0; x < 2; x++)
			{
				if (bullets[i].checkCollision(m_enemies.at(x).getPosition(), m_enemies[x].getRadius()))
				{
					m_enemies[x].setPosition(0, 0);
					bullets[i].setActive(false);
				}
			}
		}
	}
}

/// <summary>
/// Moves the enemy
/// </summary>
void GameWorld::enemyMove()
{		
	if (m_moveRight == true)
	{
		m_enemies.front().setPosition(m_enemies.front().getPosition().x +1.0f , m_enemies.front().getPosition().y);

		if (m_enemies.front().getPosition().x >= 400)
		{
			m_down = true;
			m_moveRight = false;
		}
	}

	if (m_down == true)
	{
		m_enemies.front().setPosition(m_enemies.front().getPosition().x, m_enemies.front().getPosition().y + 1.0f);

		if (m_enemies.front().getPosition().y >= 400)
		{
			m_down = false;
			m_moveLeft = true;
		}
	}

	if (m_moveLeft == true)
	{
		m_enemies.front().setPosition(m_enemies.front().getPosition().x - 1.0f, m_enemies.front().getPosition().y);

		if (m_enemies.front().getPosition().x <= 100)
		{
			m_moveLeft = false;
			m_up = true;
		}
	}

	if (m_up == true)
	{
		m_enemies.front().setPosition(m_enemies.front().getPosition().x, m_enemies.front().getPosition().y - 1.0f);

		if (m_enemies.front().getPosition().y <= 100)
		{
			m_up = false;
			m_moveRight = true;
		}
	}

	int xPos = m_enemies.back().getPosition().x;
	//std::cout << "xPos" << xPos << std::endl;
	sf::Vector2f direction = (m_player.getPosition() - m_enemies.back().getPosition());
	//sf::Vector2f newDirection = Vector3.Normalize(direction);	
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

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_window.draw(m_enemies[i]);
	}	

	for (int i = 0; i < 100; i++)
	{
		if (bullets[i].isActive())
		{
			m_window.draw(bullets[i].bulletSprite());
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

				float offsetX = ((float(rand()) / float(RAND_MAX)) * (0.1f - -0.1f)) + -0.1f;
				float offsetZ = ((float(rand()) / float(RAND_MAX)) * (0.1f - -0.1f)) + -0.1f;
				//float randomSpread = rand() % 0 + (-0.32f);
				glm::normalize(tempDirection);
				//tempDirection += tempDirection * static_cast<float>(randomSpread);

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

