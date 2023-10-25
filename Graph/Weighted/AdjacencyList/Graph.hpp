#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <forward_list>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <vector>
#include <limits>
#include <stack>
#include <queue>
#include <list>

namespace DS {
	
	class Graph {
	public:
		Graph() = default;
		Graph(int);
		Graph(const Graph&) = default;
		Graph(Graph&&) noexcept = default; 
		~Graph() = default;
	public:
		Graph& operator=(const Graph&);
		Graph& operator=(Graph&&) noexcept;
	public:
		void addVertex();
		void addEdge(int, int, double);
		void BFS(int) const;
		void DFS(int) const;
		void extraDFS(int) const;
		void removeVertex(int);
		void removeEdge(int, int);
		int getEdgeCount() const noexcept;
		int getVertexCount() const noexcept;
		int getCountOfComponents() const;
		int getWeightOfMST() const;
		[[nodiscard]] bool empty() const noexcept;
		bool hasCycle() const;
		void clear();
		void transpose();
		std::vector<std::vector<int>> allPossiblePaths(int, int) const;
		int countOfVertexesInLevel(int, int) const;
		std::vector<int> topologicalSort() const;
		std::vector<std::vector<int>> getStronglyConnectedComponents() const;
		std::vector<double> singleSourceSHortestPath(int) const;
	private:
		void stronglyConnectedComponentsHelper(int, std::vector<int>&, std::vector<int>&, std::vector<bool>&, 
										 		std::stack<int>&, std::vector<std::vector<int>>&, int&) const;
		void extraDFSHelper(int, std::vector<bool>&, bool) const;
		bool hasCycleHelper(int, int, std::vector<bool>&) const;
		bool hasCycleHelper(int, std::vector<bool>&, std::vector<bool>&) const;
		int is_visted(std::vector<bool>&) const;
		void allPossiblePathsHelper(int, int, std::vector<int>&, std::vector<std::vector<int>>&) const;
		void topologicalSortHelper(int, std::vector<bool>&, std::list<int>&) const;
	private:
		std::vector<std::forward_list<std::pair<int, double>>> m_vec;
		int m_edge_count;
	};

} //namespace DS

#endif //GRAPH_HPP_