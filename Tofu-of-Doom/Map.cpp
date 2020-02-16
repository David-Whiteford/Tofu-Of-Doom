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

		// Check if it's a wall or it's empty (this looks crappy, fix it)
		if (f_value == 2 || f_value == 3 || f_value == 4 || f_value == 5 || f_value == 6 || f_value == 7 || f_value == 8)
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
			m_lightPositions.push_back(glm::vec3(x * f_wallWidth, 150.0f, z * f_wallWidth));
		}

		// Value 4 is a floor with a fire extinguisher on it
		if (f_value == 4)
		{
			m_fireExtPositions.push_back(glm::vec3(x * f_wallWidth, -25.0f, z * f_wallWidth));
		}

		// Value 5 is a floor with an oil drum on it
		if (f_value == 5)
		{
			m_oilDrumPositions.push_back(glm::vec3(x * f_wallWidth, -20.0f, z * f_wallWidth));
		}

		// Value 6 is a floor with a chair on it
		if (f_value == 6)
		{
			m_chairPositions.push_back(glm::vec3(x * f_wallWidth, -20.0f, z * f_wallWidth));
		}

		// Value 7 is a floor with a table (type 1) on it
		if (f_value == 7)
		{
			m_table_1_Positions.push_back(glm::vec3(x * f_wallWidth, -20.0f, z * f_wallWidth));
		}

		// Value 8 is a floor with a table (type 2) on it
		if (f_value == 8)
		{
			m_table_2_Positions.push_back(glm::vec3(x * f_wallWidth, -25.0f, z * f_wallWidth));
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
/// Get the positions of the lights
/// </summary>
std::vector<glm::vec3> *Map::getLightPositions()
{
	return &m_lightPositions;
}


/// <summary>
/// Get the positions of the fire extinguishers
/// </summary>
std::vector<glm::vec3>* Map::getFireExtPositions()
{
	return &m_fireExtPositions;
}

/// <summary>
/// Get the positions of the oil drums
/// </summary>
std::vector<glm::vec3>* Map::getOilDrumPositions()
{
	return &m_oilDrumPositions;
}

/// <summary>
/// Get the positions of the chairs
/// </summary>
std::vector<glm::vec3>* Map::getChairPositions()
{
	return &m_chairPositions;
}

/// <summary>
/// Get the positions of the tables (type 1)
/// </summary>
std::vector<glm::vec3>* Map::getTable1Positions()
{
	return &m_table_1_Positions;
}

/// <summary>
/// Get the positions of the tables (type 2)
/// </summary>
std::vector<glm::vec3>* Map::getTable2Positions()
{
	return &m_table_2_Positions;
}

/// <summary>
/// Returns the address of the map array
/// </summary>
std::vector<std::pair<glm::vec3, WallType>> *Map::getMap()
{
	return &m_map;
}
