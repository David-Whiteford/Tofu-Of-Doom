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
			std::cout << "NAme " << arr[i][j] << std::endl;

			// L neighbors Algorithm:
			for (int direction = 0; direction < 9; direction++)
			{
				if (direction == 4) continue; // Skip 4, this is ourself.

				int n_row = row + ((direction % 3) - 1); // Neighbor row
				int n_col = col + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
				{
					int index = 0;
					for (int i = 0; i < ROWS; i++)
					{
						for (int j = 0; j < COLS; j++)
						{

							if (graph->nodeIndex(index)->m_data.m_row == n_row && graph->nodeIndex(index)->m_data.m_col == n_col)
							{
								graph->addArc(nodeIndex, index, m_nodeSize);
								// Add an arc from cell id 24 to cell id arr[n_row][n_col] 
								// A valid neighbor:
								std::cout << "Neighbor: " << n_row << "," << n_col << ": " << arr[n_row][n_col] << std::endl;
							}
							index++;
						}
					}

				}
			}
		}
	}
}

void Path::initAStar(std::vector<sf::RectangleShape> t_walls)
{
	graph = new Graph<NodeData, int>(2500);

	int nodeIndex = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			
			arr[i][j] = nodeIndex;
			nodeData.m_name = std::to_string(arr[i][j]);
			nodeData.m_x = i * m_nodeSize;
			nodeData.m_y = j * m_nodeSize;
			nodeData.m_row = i;
			nodeData.m_col = j;
			//add node
			graph->addNode(nodeData, nodeIndex);
			
			m_nodeShape[nodeIndex].setSize(sf::Vector2f(m_nodeSize, m_nodeSize));
			m_nodeShape[nodeIndex].setPosition(nodeData.m_x, nodeData.m_y);
			m_nodeShape[nodeIndex].setOrigin(25, 25);
			m_nodeShape[nodeIndex].setFillColor(sf::Color(sf::Color::Yellow));

			for (auto wall : t_walls)
			{
				if (m_nodeShape[nodeIndex].getGlobalBounds().intersects(wall.getGlobalBounds()))
				{
					m_nodeShape[nodeIndex].setFillColor(sf::Color(sf::Color::Black));
					nodeData.passable = false;
				}
				
			}
			m_nodeSquare.push_back(m_nodeShape[nodeIndex]);
			nodeIndex++;

		}
	}
	nodeIndex = 0;
	neighbourAlgor(nodeIndex);
	graph->aStar(graph->nodeIndex(0), graph->nodeIndex(29), graphPath);

}

void Path::update()
{
	
}

std::vector<Node*> Path::getGraphPath()
{
	return graphPath;
}
