#include "Graph.hpp"

#include <iostream>

int main() {
	DS::Graph g(3);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 1);
	// g.addEdge(1, 3);
	// g.addEdge(2, 3);
	// g.BFS(0);
	// g.transpose();
	// auto vec = g.allPossiblePaths(0, 3);
	// for (auto i : vec) {
	// 	for (auto j : i)
	// 	std::cout << j << " ";
	// 	std::cout << std::endl;
	// }
	// g.DFS(0);
	// g.extraDFS(0);
	// g.BFS(0);
	// std::cout << g.countOfVertexesInLevel(0, 1);
	// std::cout << g.getCountOfComponents();
	std::cout << std::boolalpha << g.hasCycle();
}
