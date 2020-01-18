#pragma once



#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Map.h"
#include "DisplayScale.h"

class Bullet
{
public:
	void setDamageAmount(int t_damage);
	void setActive(bool t_alive);
	bool isActive();
	int getDamageAmount();
	void setSpeed(float t_speed);

private:
	int m_damage = 1;
	bool m_alive = false;

	float speed = 5;

	// direction will need glm and sf vector for game and game world respectively

};