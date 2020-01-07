
#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "NodeData.h"
#include <map>

typedef GraphArc<NodeData, int> Arc;
typedef GraphNode<NodeData, int> Node;

void visit( Node * t_node ) 
{
	std::cout << "Visiting: " << t_node->m_data.m_name  << std::endl;
}

int main() 
{
	// Create a graph with capacity for 13 nodes.
	// Templates parameters are NodeType (std::string), ArcType (int)
    Graph<NodeData, int> graph(30 );
	std::vector<Node*> graphPath;
	std::map<std::string, int> nodeMap;
	NodeData nodeData;
	int nodeIndex = 0;

	std::ifstream myfile;
	
	
	// Create each node, and assign a name (nodeLabel) from the text file
	myfile.open ("nodes.txt");
	while ( myfile >> nodeData.m_name >> nodeData.x >> nodeData.y)
	{
		graph.addNode(nodeData, nodeIndex);
		nodeMap[nodeData.m_name] = nodeIndex;
		nodeIndex++;
	}
	
	myfile.close();

	// Wire up the graph by creating arcs between nodes.
	myfile.open("arcs.txt");
	std::string from, to;
	int weight;
	while ( myfile >> from >> to >> weight ) 
	{
		graph.addArc(nodeMap[from], nodeMap[to], weight);
	}
    myfile.close();
	Node* goal = graph.nodeIndex(5);
	// Perform a breadth-first traversal of the graph.
	//graph.breadthFirst( graph.nodeIndex(0), visit);
	// Uncomment the below to test your adapted breadth first search algorithm.
	//graph.adaptedBreadthFirst( graph.nodeIndex(0), goal);
	graph.aStar(graph.nodeIndex(0), graph.nodeIndex(29), visit, graphPath);
	//graph.ucs(graph.nodeIndex(1), graph.nodeIndex(4), visit, graphPath);
	system("PAUSE");
	return 0;
}
// Program to show the principals of generating a 2D grid using the neighbours algorithm
// as described here: https://royvanrijn.com/blog/2019/01/longest-path/
//#include <iostream>

//void main()
//{
//
//	// Construct a sample 5x5 grid - cells are numbered from 0 to 24.
//	int const ROWS = 5;
//	int const COLS = 5;
//	int arr[ROWS][COLS] =
//	{
//		{ 0, 1, 2, 3, 4 },
//		{ 5, 6, 7, 8, 9 },
//		{ 10, 11, 12, 13, 14 },
//		{ 15, 16, 17, 18, 19 },
//		{ 20, 21, 22, 23, 24 }
//	};
//
//	// Let's see if we can find the neighbours of row 4 and column 4:
//	int row = 4;
//	int col = 4;
//
//	// List all neighbors:
//	for (int direction = 0; direction < 9; direction++) {
//		if (direction == 4) continue; // Skip 4, this is ourself.
//
//		int n_row = row + ((direction % 3) - 1); // Neighbor row
//		int n_col = col + ((direction / 3) - 1); // Neighbor column
//
//		// Check the bounds:
//		if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS) 
//		{
//			// Add an arc from cell id 24 to cell id arr[n_row][n_col] 
//			// A valid neighbor:
//			std::cout << "Neighbor: " << n_row << "," << n_col << ": " << arr[n_row][n_col] << std::endl;
//		}
//	}
//}