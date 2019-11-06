#include "Map.h"

/// <summary>
/// Constructor for the Map class
/// </summary>
Map::Map()
{
	loadMap();
}

/// <summary>
/// Destructor for the Map class
/// </summary>
Map::~Map()
{

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
	float f_wallWidth = 50.0f;

	// This is for testing
	for (int i = 0; i < 10; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(i * f_wallWidth, 0.0f, 0.0f);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(i * f_wallWidth, f_wallWidth, 0.0f);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int i = 0; i < 9; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(0.0f, 0.0f, i * f_wallWidth);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(0.0f, f_wallWidth, i * f_wallWidth);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int i = 0; i < 9; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(9 * f_wallWidth, 0.0f, i * f_wallWidth);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(9 * f_wallWidth, f_wallWidth, i * f_wallWidth);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int i = 0; i < 10; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(i * f_wallWidth, 0.0f, 9 * f_wallWidth);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(i * f_wallWidth, f_wallWidth, 9 * f_wallWidth);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			glm::vec3 f_tempVec = glm::vec3(x * f_wallWidth, -f_wallWidth, y * f_wallWidth);
			WallType f_tempWallType = WallType::WALLTYPE_1;
			std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
			m_map.push_back(f_tempPair);
		}
	}

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			glm::vec3 f_tempVec = glm::vec3(x * f_wallWidth, f_wallWidth * 2, y * f_wallWidth);
			WallType f_tempWallType = WallType::WALLTYPE_1;
			std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
			m_map.push_back(f_tempPair);
		}
	}
}

/// <summary>
/// Returns the address of the map array
/// </summary>
std::vector<std::pair<glm::vec3, WallType>> *Map::getMap()
{
	return &m_map;
}
