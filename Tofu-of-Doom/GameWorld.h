#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Map.h"
#include "DisplayScale.h"
#include "Camera.h"

class GameWorld
{
public:
	GameWorld(sf::RenderWindow &t_window, sf::Time &t_deltaTime, Camera &t_camera);
	~GameWorld();
	void updateWorld();
	void enemyMove();
	void drawWorld();
	void drawBulletTrajectory();


	sf::Vector2f getPlayerPosition();
	sf::Vector2f getEnemyPosition();
	glm::vec3 getCameraPosition();

	double getPitch();
	double getYaw();
	std::vector<std::pair<glm::vec3, WallType>> *getWallData();

private:
	sf::RenderWindow &m_window;
	Camera &m_camera;
	Map *m_map = new Map();
	sf::View m_mapView;
	std::vector<std::pair<glm::vec3, WallType>> m_wallPositions;

	void setGunPosition();

	sf::CircleShape m_player;
	sf::CircleShape m_enemy;
	sf::CircleShape m_playerGun;

	std::vector<sf::CircleShape> m_enemies;
	std::vector<sf::RectangleShape> m_walls;

	glm::vec3 m_eye; // Current camera position
	double m_yaw{ 0.0 }; // Look left and right (in degrees)
	double m_pitch{ 0.0 }; // Look up and down (in degrees)
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f };

	glm::mat4 m_rotationMatrix;
	sf::Time &m_deltaTime;
	float m_speed{ 20.0f };
	float m_wallCubeSize{ 5.0f }; // This is the value of the wall cube's x, y, and z.

	bool m_moveRight{ true };
	bool m_down{ false };
	bool m_moveLeft{ true };
	bool m_up{ false };
};

#endif // !GAMEWORLD_H
