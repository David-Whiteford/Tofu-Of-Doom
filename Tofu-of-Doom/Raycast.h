#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include "GameObject.h"


class Raycast
{

public:
	Raycast();
	~Raycast();
	void setRayValues(sf::Vector2f t_startPosition, sf::Vector2f t_direction, float t_length);
	bool hit(sf::Vector2f t_targetPosition, float t_targetRadius);

	sf::VertexArray drawRay();  
	void addToHitObjects(GameObject* t_enemy);
	std::queue<GameObject *> getHitObjects();
	GameObject* getClosest();

	bool isInterpolating();

	bool intersectsRectangle(sf::Vector2f p1, sf::Vector2f p2);

	sf::Vector2f getEndPoint();

private:
	std::queue<GameObject*> hitObjects;
	GameObject *closest;

	float m_rayLength = 1000;
	sf::Vector2f m_direction;
	sf::Vector2f m_positon;

	sf::Vertex m_raycastLine[2];

	bool interpolate = false;
	bool findEntrancePoint = false;
	bool findExitPoint = false;
	bool findAllCollisions = false;

	//bool raycastHit = false;


};