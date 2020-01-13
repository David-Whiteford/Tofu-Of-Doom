#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "aStarStuff/Graph.h"
#include "aStarStuff/NodeData.h"

class Path
{
public:
	Path(sf::RenderWindow& t_window);
	~Path();
	void draw();
	void neighbourAlgor(int nodeIndex);
	void initAStar();

private:
	sf::RenderWindow& m_window;
	std::map<std::string, int> nodeMap;
	Graph<NodeData, int>* graph;
	std::vector<NodeData*> graphPath;

	NodeData nodeData;
	int nodeIndex{ 0 };

	std::vector<sf::RectangleShape> m_nodeSquare;
	int val = 0;
	int static const ROWS = 5;
	int static const COLS = 5;
	int arr[ROWS][COLS] =
	{
		{ 0, 1, 2, 3, 4 },
		{ 5, 6, 7, 8, 9 },
		{ 10, 11, 12, 13, 14 },
		{ 15, 16, 17, 18, 19 },
		{ 20, 21, 22, 23, 24 }
	};


	//find the neighbours of row 4 and column 4(temp Test
	int row = 0;
	int col = 0;

	sf::RectangleShape m_nodeShape;
	int m_nodeSize = 20;
};


