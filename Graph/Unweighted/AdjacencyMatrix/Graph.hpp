#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <vector>
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
		void addEdge(int, int);
		void BFS(int) const;
		void DFS(int) const;
		void extraDFS(int) const;
		void removeVertex(int);
		void removeEdge(int, int);
		int getEdgeCount() const noexcept;
		int getVertexCount() const noexcept;
		int getCountOfComponents() const;
		bool hasCycle() const;
		[[nodiscard]] bool empty() const noexcept;
		void clear();
		void transpose();
		std::vector<int> shortestPath(int, int) const;
		std::vector<std::vector<int>> allPossiblePaths(int, int) const;
		int countOfVertexesInLevel(int, int) const;
		std::vector<int> topologicalSort() const;
		std::vector<std::vector<int>> getStronglyConnectedComponents() const;
	private:
		void stronglyConnectedComponentsHelper(int, std::vector<int>&, std::vector<int>&, std::vector<bool>&, 	
												std::stack<int>&, std::vector<std::vector<int>>&, int&) const;
		bool hasCycleHelper(int, int, std::vector<bool>&) const;
		bool hasCycleHelper(int, std::vector<bool>&, std::vector<bool>&) const;
		void extraDFSHelper(int, std::vector<bool>&, bool) const;
		void allPossiblePathsHelper(int, int, std::vector<int>&, std::vector<std::vector<int>>&) const;
		int is_visted(std::vector<bool>&) const;
		void topologicalSortHelper(int, std::vector<bool>&, std::list<int>&) const;
	private:
		std::vector<std::vector<bool>> m_vec;
		int m_edge_count;
	};

} //namespace DS

#endif //GRAPH_HPP_
