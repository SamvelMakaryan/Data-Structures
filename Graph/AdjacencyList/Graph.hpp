#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <forward_list>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <utility>
#include <vector>
#include <stack>
#include <queue>

namespace DS {
	
	class Graph {
	public:
		Graph() = default;
		Graph(std::size_t);
		Graph(const Graph&) = default;
		Graph(Graph&&) noexcept = default; 
		~Graph() = default;
	public:
		Graph& operator=(const Graph&);
		Graph& operator=(Graph&&) noexcept;
	public:
		void addVertex();
		void addEdge(std::size_t, std::size_t);
		void BFS(std::size_t) const;
		void DFS(std::size_t) const;
		void extraDFS(std::size_t) const;
		void removeVertex(std::size_t);
		void removeEdge(std::size_t, std::size_t);
		std::size_t getEdgeCount() const noexcept;
		std::size_t getVertexCount() const noexcept;
		std::size_t getCountOfComponents() const;
		[[nodiscard]] bool empty() const noexcept;
		void clear();
		void transpose();
		std::vector<std::size_t> shortestPath(std::size_t, std::size_t) const;
		std::vector<std::vector<std::size_t>> allPaths(std::size_t, std::size_t) const;
	private:
		void extraDFSHelper(std::size_t, std::vector<bool>&, bool) const;
		long is_visted(std::vector<bool>&) const;
	private:
		std::vector<std::forward_list<std::size_t>> m_vec;
		std::size_t m_edge_count;
	};

} //namespace DS

#endif //GRAPH_HPP_


