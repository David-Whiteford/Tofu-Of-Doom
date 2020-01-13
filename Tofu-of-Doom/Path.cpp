#include "Path.h"

Path::Path(sf::RenderWindow& t_window):
	m_window(t_window)
{
}

Path::~Path()
{
}

void Path::draw()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		for (auto node : m_nodeSquare)
		{
			m_window.draw(node);
		}
	}
}



void Path::neighbourAlgor(int nodeIndex)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
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

					if (nodeData.m_row == n_row && nodeData.m_col == n_col)
					{
						graph->addArc(nodeMap[nodeData.m_name], arr[n_row][n_col], 10);
						// Add an arc from cell id 24 to cell id arr[n_row][n_col] 
						// A valid neighbor:
						std::cout << "Neighbor: " << n_row << "," << n_col << ": " << arr[n_row][n_col] << std::endl;
					}
					nodeIndex++;

				}
			}
		}
	}
}

void Path::initAStar()
{

	
	
	graph = new Graph<NodeData, int>(25);

	int nodeIndex = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			
			nodeData.m_name = arr[i][j];
			nodeData.m_x = i * m_nodeSize;
			nodeData.m_y = j * m_nodeSize;

			graph->addNode(nodeData, nodeIndex);
			

			m_nodeShape.setSize(sf::Vector2f(m_nodeSize, m_nodeSize));
			m_nodeShape.setFillColor(sf::Color(sf::Color::Blue));
			m_nodeShape.setPosition(i * m_nodeSize, j * m_nodeSize);
			m_nodeSquare.push_back(m_nodeShape);
			nodeIndex++;
		
		}
	}
	nodeIndex = 0;
	neighbourAlgor(nodeIndex);
}
