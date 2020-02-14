#pragma once
#include "GameObject.h"



#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "WallType.h"


class Wall : public GameObject
{
public:
	Wall(sf::RenderWindow& t_window,float size,sf::Vector2f pos) : 
		m_window(t_window) 
	{
		m_wall.setPosition(pos); 
		m_wall.setFillColor(sf::Color::Green);
		m_wall.setSize(sf::Vector2f(size, size));
		m_wall.setOrigin(sf::Vector2f(size / 2, size / 2));
		myGameObject = dynamic_cast<GameObject*>(this);
		myGameObject->setTag(WALL_TAG);

	} // end wall
	virtual ~Wall() {}
	sf::RectangleShape getShape() { return m_wall; }
	void setPosition(sf::Vector2f(t_pos)) { m_wall.setPosition(t_pos); }
	void setShape(sf::RectangleShape shapeParam) { m_wall = shapeParam; }
	void draw() { m_window.draw(m_wall); }
	GameObject *myGameObject;

private:

	sf::RenderWindow& m_window;
	glm::vec3 m_wallPositions = {glm::vec3(0,0,0)};

	sf::RectangleShape m_wall;
};