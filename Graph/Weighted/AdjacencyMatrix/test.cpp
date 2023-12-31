#include "Graph.hpp"
#include <iostream>

int main() {
    DS::Graph g(6);
    g.addEdge(5, 2, 1.2);
    g.addEdge(5, 0, 1.4);
    g.addEdge(4, 0, 3.5);
    g.addEdge(4, 1, 1.0);
    g.addEdge(2, 3, 11.2);
    g.addEdge(3, 1, 1.344);
    std::cout << "Graph DFS traversal starting from 0" << std::endl;
    g.DFS(0);
    std::cout << "Count of vertexes  -  " << g.getVertexCount() << std::endl; 
    std::cout << "Count of edge  -  " << g.getEdgeCount() << std::endl; 
    std::cout << "Count of components  -  " << g.getCountOfComponents() << std::endl;
    std::cout << "Graph BFS traversal starting from 0" << std::endl;
    g.BFS(0);
    std::cout << "Graph DFS traversal on all components starting from 0" << std::endl;
    g.extraDFS(0);
    std::cout << "Graph topological sorting" << std::endl;
    auto sort = g.topologicalSort();
    for (auto i : sort) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "All possible paths from 4 to 5" << std::endl;
    auto paths = g.allPossiblePaths(2, 3);
    for (auto i : paths) {
        for (auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Does graph has cycle  -  " << std::boolalpha << g.hasCycle() << std::endl;
    std::cout << "Count of nodes in level 1 from 4  -  " << g.countOfVertexesInLevel(4, 1) << std::endl;
    g.addEdge(3, 5, 7);
    std::cout << "Strongly connected components"<< std::endl;
    auto components = g.getStronglyConnectedComponents();
    for (auto i : components) {
        for (auto j : i) {
            std::cout << j << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "All shortest distances from vertex 3" << std::endl;
    auto distances = g.singleSourceSHortestPath(3);
    for (auto i : distances) {
        if (i == std::numeric_limits<double>::infinity()) {
            std::cout << "INF ";
        } else {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
    DS::Graph g2(5);
    g2.addEdge(0, 1, 10);
    g2.addEdge(1, 0, 10);
    g2.addEdge(0, 2, 5);
    g2.addEdge(2, 0, 5);
    g2.addEdge(1, 3, 2);
    g2.addEdge(3, 1, 2);
    g2.addEdge(3, 0, 0);
    g2.addEdge(0, 3, 0);
    g2.addEdge(3, 2, 1);
    g2.addEdge(2, 3, 1);
    g2.addEdge(1, 4, 11);
    g2.addEdge(4, 1, 11);
    std::cout << "The weight of Minimum spannig tree of graph is  -  " << g2.getWeightOfMST() << std::endl;
    std::cout << std::endl;
}