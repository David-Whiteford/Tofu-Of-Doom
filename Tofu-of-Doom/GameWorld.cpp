#include "GameWorld.h"

/// <summary>
/// Constructor for the GameWorld class
/// </summary>
GameWorld::GameWorld(sf::RenderWindow &t_window, sf::Time &t_deltaTime, Camera &t_camera) 
	: m_window(t_window), m_deltaTime(t_deltaTime), m_camera(t_camera)
{
	// Player
	m_player.setRadius(25.0f);
	m_player.setFillColor(sf::Color::Red);
	m_player.setOrigin(sf::Vector2f(25.0f, 25.0f));
	m_player.setPosition(m_camera.getEye().x, m_camera.getEye().z); // Test starting position
	// m_eye = glm::vec3(m_player.getPosition().x, 2.0f, m_player.getPosition().y);

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
}

/// <summary>
/// Game controls
/// </summary>
void GameWorld::gameControls()
{
	// Move left OR right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		glm::vec4 tempDirection_1(m_direction.x, m_direction.y, m_direction.z, 1.0f);
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.f, 1.f, 0.f));
		tempDirection_1 = tempDirection_1 * m_rotationMatrix;
		glm::normalize(tempDirection_1);
		glm::vec3 tempDirection_2(tempDirection_1.x, tempDirection_1.y, tempDirection_1.z);
		m_eye -= tempDirection_2 * static_cast<float>(m_deltaTime.asSeconds() * m_speed * 2.0f);
		m_player.setPosition(m_eye.x * 12.0f, m_eye.z * 12.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		glm::vec4 tempDirection_1(m_direction.x, m_direction.y, m_direction.z, 1.0f);
		m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.f, 1.f, 0.f));
		tempDirection_1 = tempDirection_1 * m_rotationMatrix;
		glm::normalize(tempDirection_1);
		glm::vec3 tempDirection_2(tempDirection_1.x, tempDirection_1.y, tempDirection_1.z);
		m_eye -= tempDirection_2 * static_cast<float>(m_deltaTime.asSeconds() * m_speed * 2.0f);
		m_player.setPosition(m_eye.x * 12.0f, m_eye.z * 12.0f);
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

