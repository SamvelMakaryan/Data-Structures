#include "Graph.hpp"
#include <iostream>

int main() {
    DS::Graph g(3);
    g.addVertex();
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(0, 3);
    // g.extraDFS(0);
    // std::cout << g.getCountOfComponents();
//    auto v =  g.shortestPath(0, 3);
//    for (auto& vec : v) {
//     std::cout << vec << " ";
//    }
    // auto vec = g.allPossiblePaths(0, 3);
    // for (auto i : vec) {
    //     for (auto j : i) {
    //         std::cout << j << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::boolalpha << g.hasCycle();
    std::cout << g.countOfVertexesInLevel(1, 1);
}