#include "Map.h"

/// <summary>
/// Constructor for the Map class
/// </summary>
Map::Map()
{
	loadMapData("level_data/level_1_map.txt", m_map);
}

/// <summary>
/// Destructor for the Map class
/// </summary>
Map::~Map()
{

}

/// <summary>
/// Reads map data from an external .txt file
/// </summary>
void Map::loadMapData(std::string t_fileName, std::vector<std::pair<glm::vec3, WallType>> &t_array)
{
	float f_wallWidth = 50.0f; // The width / depth / height of the wall in pixels
	int f_mapWidth = 50; // How many tiles wide the map is

	std::ifstream f_textFile(t_fileName);
	std::string f_line;
	int f_value;
	std::pair<glm::vec3, WallType> f_tempPair;
	glm::vec3 f_tempVec;
	WallType f_tempWallType;
	int x = 0;
	int z = 0;

	while (std::getline(f_textFile, f_line, ','))
	{
		f_value = (int)std::atof(f_line.c_str());

		// Check if it's a wall or it's empty
		if (f_value == 2 || f_value == 3)
		{
			f_tempWallType = WallType::EMPTY;
		}
		else if (f_value == 1)
		{
			f_tempWallType = WallType::WALLTYPE_1;
		}

		// Value 3 is a floor with a light above it
		if (f_value == 3)
		{
			m_lightPositions.push_back(glm::vec3(x * f_wallWidth, 100.0f, z * f_wallWidth));
		}

		f_tempPair = std::make_pair(glm::vec3(x * f_wallWidth, 0.0f, z * f_wallWidth), f_tempWallType);
		t_array.push_back(f_tempPair);

		x++;

		if (x == f_mapWidth)
		{
			x = 0;
			z++;
		}
	}
}

/// <summary>
/// Loads a map
/// </summary>
void Map::loadMap()
{
	// The map now uses pixels instead of OpenGL units for measurement
	// 10 pixels is equal to 1 OpenGL unit
	//
	// f_wallWidth is the width, height and depth of a single wall cube
	// A wall cube of 5 x 5 x 5 OpenGL units is a suitable size for a wall
	// This equates to 50 x 50 x 50 pixels
	//
	// Clementine will remember that.....
	//float f_wallWidth = 50.0f;

	//// This is for testing
	//for (int i = 0; i < 10; ++i)
	//{
	//	glm::vec3 f_tempVec = glm::vec3(i * f_wallWidth, 0.0f, 0.0f);
	//	WallType f_tempWallType = WallType::WALLTYPE_1;
	//	std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);

	//	f_tempVec = glm::vec3(i * f_wallWidth, f_wallWidth, 0.0f);
	//	f_tempWallType = WallType::WALLTYPE_1;
	//	f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);
	//}

	//for (int i = 0; i < 9; ++i)
	//{
	//	glm::vec3 f_tempVec = glm::vec3(0.0f, 0.0f, i * f_wallWidth);
	//	WallType f_tempWallType = WallType::WALLTYPE_1;
	//	std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);

	//	f_tempVec = glm::vec3(0.0f, f_wallWidth, i * f_wallWidth);
	//	f_tempWallType = WallType::WALLTYPE_1;
	//	f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);
	//}

	//for (int i = 0; i < 9; ++i)
	//{
	//	glm::vec3 f_tempVec = glm::vec3(9 * f_wallWidth, 0.0f, i * f_wallWidth);
	//	WallType f_tempWallType = WallType::WALLTYPE_1;
	//	std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);

	//	f_tempVec = glm::vec3(9 * f_wallWidth, f_wallWidth, i * f_wallWidth);
	//	f_tempWallType = WallType::WALLTYPE_1;
	//	f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);
	//}

	//for (int i = 0; i < 10; ++i)
	//{
	//	glm::vec3 f_tempVec = glm::vec3(i * f_wallWidth, 0.0f, 9 * f_wallWidth);
	//	WallType f_tempWallType = WallType::WALLTYPE_1;
	//	std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);

	//	f_tempVec = glm::vec3(i * f_wallWidth, f_wallWidth, 9 * f_wallWidth);
	//	f_tempWallType = WallType::WALLTYPE_1;
	//	f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//	m_map.push_back(f_tempPair);
	//}

	//for (int y = 0; y < 10; ++y)
	//{
	//	for (int x = 0; x < 10; ++x)
	//	{
	//		glm::vec3 f_tempVec = glm::vec3(x * f_wallWidth, -f_wallWidth, y * f_wallWidth);
	//		WallType f_tempWallType = WallType::WALLTYPE_1;
	//		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//		m_map.push_back(f_tempPair);
	//	}
	//}

	//for (int y = 0; y < 10; ++y)
	//{
	//	for (int x = 0; x < 10; ++x)
	//	{
	//		glm::vec3 f_tempVec = glm::vec3(x * f_wallWidth, f_wallWidth * 2, y * f_wallWidth);
	//		WallType f_tempWallType = WallType::WALLTYPE_1;
	//		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
	//		m_map.push_back(f_tempPair);
	//	}
	//}
}

std::vector<glm::vec3> *Map::getLightPositions()
{
	return &m_lightPositions;
}

/// <summary>
/// Returns the address of the map array
/// </summary>
std::vector<std::pair<glm::vec3, WallType>> *Map::getMap()
{
	return &m_map;
}
