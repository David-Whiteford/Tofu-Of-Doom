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
	float f_wallWidth;

	// This is for testing
	for (int i = 0; i < 10; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(i * 5.0f, 0.0f, 0.0f);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(i * 5.0f, 5.0f, 0.0f);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int i = 0; i < 9; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(0.0f, 0.0f, i * 5.0f);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(0.0f, 5.0f, i * 5.0f);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int i = 0; i < 9; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(9 * 5.0f, 0.0f, i * 5.0f);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(9 * 5.0f, 5.0f, i * 5.0f);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int i = 0; i < 10; ++i)
	{
		glm::vec3 f_tempVec = glm::vec3(i * 5.0f, 0.0f, 9 * 5.0f);
		WallType f_tempWallType = WallType::WALLTYPE_1;
		std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);

		f_tempVec = glm::vec3(i * 5.0f, 5.0f, 9 * 5.0f);
		f_tempWallType = WallType::WALLTYPE_1;
		f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
		m_map.push_back(f_tempPair);
	}

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			glm::vec3 f_tempVec = glm::vec3(x * 5.0f, -5.0f, y * 5.0f);
			WallType f_tempWallType = WallType::WALLTYPE_1;
			std::pair<glm::vec3, WallType> f_tempPair = std::make_pair(f_tempVec, f_tempWallType);
			m_map.push_back(f_tempPair);
		}
	}

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			glm::vec3 f_tempVec = glm::vec3(x * 5.0f, 10.0f, y * 5.0f);
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
