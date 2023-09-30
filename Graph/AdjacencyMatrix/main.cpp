#include "Graph.hpp"
#include <iostream>

int main() {
    DS::Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addVertex();
    // g.addEdge(0, 3);
    // g.extraDFS(0);
    // std::cout << g.getCountOfComponents();
   auto v =  g.shortestPath(0, 3);
   for (auto& vec : v) {
    std::cout << vec << " ";
   }
}