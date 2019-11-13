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
	// m_eye = glm::vec3(m_player.getPosition().x, 2.0f, m_player.getPosition().y);

	
	m_enemy.setRadius(25.0f);
	m_enemy.setFillColor(sf::Color::Red);
	m_enemy.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_enemy.setPosition(100,100); // Test starting position

	// View
	m_mapView.setViewport(sf::FloatRect(0.25f, 0.25f, 0.5f, 0.5f));
	m_mapView.setSize(m_window.getSize().x, m_window.getSize().y);

	// Create an array to store the walls in
	for (int i = 0; i < m_map->getMap()->size(); ++i)
	{
		sf::RectangleShape f_tempWall;
		f_tempWall.setSize(sf::Vector2f(s_wallWidth, s_wallWidth));
		f_tempWall.setOrigin(s_wallWidth / 2.0f, s_wallWidth / 2.0f);
		f_tempWall.setFillColor(sf::Color::Green);
		f_tempWall.setPosition(m_map->getMap()->at(i).first.x, m_map->getMap()->at(i).first.z);
		m_walls.push_back(f_tempWall);
	}
}

/// <summary>
/// Constructor for the GameWorld class
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
	enemyMove();
}

void GameWorld::enemyMove()
{		
	if (m_moveRight == true)
	{
		m_enemy.setPosition(m_enemy.getPosition().x +1.0f , m_enemy.getPosition().y);

		if (m_enemy.getPosition().x >= 400)
		{
			m_down = true;
			m_moveRight = false;
		}
	}

	if (m_down == true)
	{
		m_enemy.setPosition(m_enemy.getPosition().x, m_enemy.getPosition().y + 1.0f);

		if (m_enemy.getPosition().y >= 400)
		{
			m_down = false;
			m_moveLeft = true;
		}
	}

	if (m_moveLeft == true)
	{
		m_enemy.setPosition(m_enemy.getPosition().x - 1.0f, m_enemy.getPosition().y);

		if (m_enemy.getPosition().x <= 100)
		{
			m_moveLeft = false;
			m_up = true;
		}
	}

	if (m_up == true)
	{
		m_enemy.setPosition(m_enemy.getPosition().x, m_enemy.getPosition().y - 1.0f);

		if (m_enemy.getPosition().y <= 100)
		{
			m_up = false;
			m_moveRight = true;
		}
	}
}

/// <summary>
/// Draw the world
/// </summary>
void GameWorld::drawWorld()
{
	// gameControls(); // This function shouldn't be here. It's evil. IT'S EVIL I TELLS YA!
 
	for (int i = 0; i < m_walls.size(); ++i)
	{
		m_window.draw(m_walls[i]);
	}

	m_mapView.setCenter(m_player.getPosition());
	m_window.setView(m_mapView);
	m_window.draw(m_player);
	m_window.draw(m_enemy);
}

/// <summary>
/// Returns the position of the player's origin
/// </summary>
sf::Vector2f GameWorld::getPlayerPosition()
{
	return m_player.getPosition();
}

sf::Vector2f GameWorld::getEnemyPosition()
{
	return m_enemy.getPosition();
}

/// <summary>
/// Returns the position of the camera
/// </summary>
glm::vec3 GameWorld::getCameraPosition()
{
	return m_eye;
}

double GameWorld::getPitch()
{
	return m_pitch;
}

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

