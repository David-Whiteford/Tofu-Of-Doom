#ifndef MAP_H
#define MAP_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "WallType.h"
#include "DisplayScale.h"

class Map
{
public:
	Map();
	~Map();
	void loadMap();
	std::vector<std::pair<glm::vec3, WallType>> *getMap();

private:
	std::vector<std::pair<glm::vec3, WallType>> m_map;
};

#endif // !MAP_H
