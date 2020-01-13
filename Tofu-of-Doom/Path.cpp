#include "Path.h"

Path::Path()
{
}

Path::~Path()
{
}

void Path::draw(sf::RenderWindow& t_window)
{
}

void Path::neighbourAlgor()
{

	// L neighbors Algorithm:
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue; // Skip 4, this is ourself.

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
		{
			graph->addArc(nodeMap[nodeData.m_name], arr[n_row][n_col], 10);
			// Add an arc from cell id 24 to cell id arr[n_row][n_col] 
			// A valid neighbor:
			std::cout << "Neighbor: " << n_row << "," << n_col << ": " << arr[n_row][n_col] << std::endl;
		}
	}
}

void Path::initAStar()
{
	graph = new Graph<NodeData, int>(25);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int index = 0;
			nodeData.m_name = arr[i][j];
			graph->addNode(nodeData, index);
			int val = arr[i][j];
			std::cout << val << std::endl;

		}
	}

	nodeData.x = 50;
	nodeData.y = 50;
	nodeData.pathCost = 50;
}
