#include "Graph.hpp"

#include <iostream>

int main() {
	DS::Graph g;
	g.addVertex();
	g.addVertex();
	g.addVertex();
	g.addVertex();
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	// g.BFS(0);
	// g.DFS(0);
	g.extraDFS(0);
	// std::cout << g.getCountOfComponents();
}
