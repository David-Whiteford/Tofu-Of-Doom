#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/OpenGL.hpp>

#include "Path.h"
#include "Map.h"
#include "DisplayScale.h"
#include "Camera.h"
#include "Bullet.h"
#include "Transform.h"
#include "ProjectileEnemy.h"

#include <stdlib.h>
#include <ctime>

#include "Enemy.h"
#include "Wall.h"
#include "Quadtree.h"
#include "UI.h"
#include "Player.h"

class GameWorld
{
public:
	GameWorld(sf::RenderWindow &t_window, sf::Time &t_deltaTime, Camera *t_camera);
	~GameWorld();
	void updateWorld();
	void drawWorld();

	void initialise();
	int getPlayerHealth();
	void drawUI(int t_gunType);
	bool fireBullet(int t_gunType);
	void reload(int t_guntType);
	void checkPlayerRayCollsions(sf::Time t_deltaTime); 
	void updateBulletPhysics();
	int getActiveEnemyCount();
	void checkEnemyInQueueAlive();
	void populateQuadtree();

	Bullet *bullets[100];
	std::vector<Bullet*> activeBullets; // For a smaller loop
	
	ProjectileEnemy* enemyBullet[10];
	int firedAt = 110;
	int fireWait = 45;


	void ShootTowardsPlayer();




	float Pi = 3.14;
	sf::Vector2f getPlayerPosition();
	glm::vec3 getCameraPosition();
	sf::Vector2f getEnemyPosition(int index);
	double getPitch();
	double getYaw();
	std::vector<std::pair<glm::vec3, WallType>> *getWallData();
	std::vector<glm::vec3> *getLightPositions();

	UI ui;
	sf::View ui_view;

	std::vector<glm::vec3> *getFireExtPositions();
	std::vector<glm::vec3> *getOilDrumPositions();
	std::vector<glm::vec3> *getChairPositions();
	std::vector<glm::vec3> *getTable1Positions();
	std::vector<glm::vec3> *getTable2Positions();
	float getEnemySize(int index);


	bool hitWall = false;
	sf::Vector2f hitPos;

private:

	Graph<NodeData, int>* graph;

	std::map<std::string, int> nodeMap;
	NodeData nodeData;
	int nodeIndex{ 0 };
	std::ifstream myfile;

	// Find the neighbours of row 4 and column 4
	int row = 0;
	int col = 0;


	Quadtree quadtree = Quadtree(-50, -50, 2550, 2550, 0, 6);
	Quadtree quadtreeMoving = Quadtree(-50, -50, 2550, 2550, 0, 2);
	Quadtree quadtreeBullet = Quadtree(-500, -500, 3550, 3550, 0, 4);
	Path* m_gamePath = new Path(m_window);
	Enemy* m_enemyVec[99];

	std::vector<GameObject*> previousReturn;
	std::vector<GameObject*> returnWall;
	std::vector<Node*> graphPath;
	std::vector<int> m_startNodes;
	std::vector<int> m_endNodes;
	int m_currentNode = 0;
	int m_endNode = 0;
	int m_playerNode = 0;
	int m_enemyNode = 0;
	Transform m_transform;
	Transform::Position enemyPos;
	Transform::Position graphPos;
	sf::CircleShape m_enemy;
	sf::RenderWindow &m_window;
	sf::Vector2f previousPos;
	bool follow = false;

	// We will use the q to push and pop checking collisions
	std::vector<Enemy*> m_enemyActive;

	// Walls
	std::vector<Wall*> m_wallVec;
	float m_wallCubeSize{ 5.0f }; // This is the value of the wall cube's x, y, and z.

	Camera &m_camera;
	Player m_player;
	Map *m_map = new Map();
	sf::View m_mapView;
	sf::Vector2f m_newPosition;
	sf::Time& m_deltaTime;
	sf::CircleShape m_playerGun;
	std::vector<sf::Vector2f> m_startingPos;
	glm::vec3 m_eye; // Current camera position
	glm::vec4 m_direction{ 0.f, 0.f, 1.f, 0.f };
	glm::mat4 m_rotationMatrix;
	double m_yaw{ 0.0 }; // Look left and right (in degrees)
	double m_pitch{ 0.0 }; // Look up and down (in degrees)
	double const DEG_TO_RAD = Pi / 180.0f;
	float m_speed{ 20.0f };
	float m_speedEn{ 5.0f };
	int m_radius = 5;
	bool m_moveRight{ true };
	bool m_down{ false };
	bool m_moveLeft{ true };
	bool m_up{ false };

	// Functions
	void setGunPosition();
};

#endif // !GAMEWORLD_H
