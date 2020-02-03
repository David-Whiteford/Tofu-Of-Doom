#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "aStarStuff/Graph.h"
#include "aStarStuff/NodeData.h"
#include "Transform.h"
typedef GraphNode<NodeData, int> Node;
class Path
{
public:
	Path(sf::RenderWindow& t_window);
	~Path();
	void draw();
	void neighbourAlgor();
	void initAStar(std::vector<sf::RectangleShape> t_walls);
	void update();
	void setPath();
	void setNewPath();
	void newPath(int t_start, int t_end );
	std::vector<Node*> &getGraphPath();
	Transform m_transform;
	int nodePos(sf::Vector2f position);

private:
	sf::RenderWindow& m_window;
	std::map<std::string, int> nodeMap;
	Graph<NodeData, int>* graph;
	int endNode = 2237;
	int startNode = 103;
	


	std::vector<Node*> graphPath;

	std::vector<std::vector<Node*>> paths;
	NodeData nodeData;
	int nodeIndex{ 0 };

	std::vector<sf::RectangleShape> m_nodeSquare;
	int val = 0;
	int static const ROWS = 50;
	int static const COLS = 50;
	int arr[ROWS][COLS];



	//find the neighbours of row 4 and column 4(temp Test
	int row = 0;
	int col = 0;

	sf::RectangleShape m_nodeShape[2500];
	int m_nodeSize = 50;
};
