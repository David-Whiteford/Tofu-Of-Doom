#ifndef MAP_H
#define MAP_H

#include "libs/glew/glew.h"
#include "libs/glew/wglew.h"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>

#include "WallType.h"
#include "DisplayScale.h"

class Map
{
public:
	Map();
	~Map();
	void loadMapData(std::string t_fileName, std::vector<std::pair<glm::vec3, WallType>> &t_array);
	std::vector<std::pair<glm::vec3, WallType>> *getMap();
	void loadMap();
	std::vector<glm::vec3> *getLightPositions();

private:
	std::vector<std::pair<glm::vec3, WallType>> m_map;
	std::vector<glm::vec3> m_lightPositions;
};

#endif // !MAP_H
