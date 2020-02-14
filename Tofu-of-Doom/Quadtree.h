#pragma once
#include <iostream>
#include "GameObject.h"
#include <vector>


///<summary>
/// Grid based Quadtree
///
///</summary>

static int checks;
class Quadtree
{
public:
	Quadtree() {};
	Quadtree(float posX, float posY, float height, float width, int currentLevel, int maxLevel);
	~Quadtree();

	void addObject(GameObject* gameObject);
	std::vector<GameObject*> getObjectsAt(float x, float y,float _size);
	std::vector<GameObject*> getObjectsBetweenPoints(float start_x, float startY, float endX, float endY);
	bool Quadtree::intersects(Quadtree otherQuad);
	void clear();
	

	void Quadtree::draw(sf::RenderTarget& canvas, std::vector<GameObject*> returned);


private:


	float m_posX;
	float m_posY;
	float m_width;
	float m_height;
	int m_currentLevel;
	int	m_maxLevel;
	std::vector<GameObject*> gameObjectsVec;

	bool containsObject(Quadtree* child, GameObject* object);


	Quadtree* m_topLeft;
	Quadtree* m_topRight;
	Quadtree* m_bottomLeft;
	Quadtree* m_bottomRight;

	sf::RectangleShape shape;
};