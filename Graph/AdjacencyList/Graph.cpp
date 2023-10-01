#include "Graph.hpp"

namespace DS {
	
	Graph::Graph(int count) 
	: m_vec(count),
	  m_edge_count(0) {}
	
	bool Graph::empty() const noexcept {
		return m_vec.empty();
	}

	int Graph::getEdgeCount() const noexcept {
		return m_edge_count;
	}	
	
	int Graph::getVertexCount() const noexcept {
		return m_vec.size();
	}	

	Graph& Graph::operator=(const Graph& rhs) {
		if (this != &rhs) {
			m_vec = rhs.m_vec;
			m_edge_count = rhs.m_edge_count;
		}
		return *this;
	}	
	
	Graph& Graph::operator=(Graph&& rhs) noexcept {
		if (this != &rhs) {
			m_vec = std::move(rhs.m_vec);
			m_edge_count = rhs.m_edge_count;
		}
		return *this;
	}	
	
	void Graph::addVertex() {
		m_vec.push_back(std::forward_list<int>{});
	}
	
	void Graph::addEdge(int src, int dest) {
		if (dest >= m_vec.size()) {
			throw std::invalid_argument("The 'edge' should connect consisting elements.");
		}	
		++m_edge_count;
		m_vec[src].emplace_front(dest);
		//for undirected
		//m_vec[dest].emplace_front(src);
		//++m_edge_count;
	}
	
	void Graph::removeEdge(int src, int dest) {
		if (dest > m_vec.size() || src > m_vec.size()) {
			throw std::invalid_argument("The 'edge' doesn't exist.");
		}	
		m_vec[src].remove_if([this, dest](const auto& val) {
			if (val == dest) {
				--m_edge_count;
				return true;
			} else {
				return false;
			}
		});
		//for undirected
	//	m_vec[dest].remove_if([this, src](const auto& val) {
	//		if (val == src) {
	//			--m_edge_count;
	//			return true;
	//		} else {
	//			return false;
	//		}
	//	};
	}

	void Graph::removeVertex(int v) {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		for (auto i : m_vec[v]) {
			m_vec[i].remove_if([this, v](const auto& val) {
				if (val == v) {
					--m_edge_count;
					return true;
				} else {
					return false;
				}
			});
		}
		m_vec.erase(m_vec.begin() + v);
	}

	void Graph::clear() {
		m_vec.clear();
	}
		
	void Graph::BFS(int v) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		std::vector<bool> visited(m_vec.size(), false);
		std::queue<int> q;
		q.push(v);
		visited[v] = true;
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				int tmp = q.front();
				q.pop(); 
				std::cout << tmp << " ";
				for (const auto& i : m_vec[tmp]) {
					if (!visited[i]) {
						visited[i] = true;
						q.push(i);
					}
				}
			}
			std::cout << std::endl;
		}
	}

	void Graph::extraDFS(int v) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		std::vector<bool> visited(m_vec.size(), false);
		int ver = v;
		while (ver != -1) {
			extraDFSHelper(ver, visited, true);
			ver = is_visted(visited);
		}
		std::cout << std::endl;
	}

	void Graph::extraDFSHelper(int v, std::vector<bool>& visited, bool print) const {
		visited[v] = true;
		if (print) {
			std::cout << v << " ";
		}
		for (auto i : m_vec[v]) {
			if (!visited[i]) {
				extraDFSHelper(i, visited, print);
			}
		}
	}

	int Graph::is_visted(std::vector<bool>& vec) const {
		for (int i = 0; i < vec.size(); ++i) {
			if (!vec[i]) {
				return i;
			}
		}
		return -1;
	}

	int Graph::getCountOfComponents() const {
		if (m_vec.empty()) {
			return 1;
		}
		int components = 0;
		std::vector<bool> visited(m_vec.size(), false);
		int ver = 0;
		while (ver != -1) {
			++components;
			extraDFSHelper(ver, visited, false);
			ver = is_visted(visited);
		}
		return components;
	}

	void Graph::DFS(int v) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		std::vector<bool> visited(m_vec.size(), false);
		std::stack<int> s;
		s.push(v);
		visited[v] = true;
		while (!s.empty()) {
			int tmp = s.top();
			s.pop();
			std::cout << tmp << " ";
			for (const auto& i : m_vec[tmp]) {
				if (!visited[i]) {
					visited[i] = true;
					s.push(i);
				}
			}
		}
		std::cout << std::endl;
	}

	void Graph::transpose() {
		Graph tmp(m_vec.size());
		for (int i = 0; i < m_vec.size(); ++i) {
			for (auto v : m_vec[i]) {
				tmp.m_vec[v].push_front(i);
			}
		}
		*this = tmp;
	}

	std::vector<int> Graph::shortestPath(int src, int dest) const {
		if (dest > m_vec.size() || src > m_vec.size()) {
			throw std::invalid_argument("The 'vertex' doesn't exist.");
		}
		if (src == dest) {
			return {src};
		}
		std::vector<int> vec;
		std::queue<int> q;
		std::vector<bool> visited(m_vec.size(), false);
		std::vector<int> parents(m_vec.size(), -1);
		q.push(src);
		visited[src] = true;
		while (!q.empty()) {
			int tmp = q.front();
			q.pop();
			if (tmp == dest) {
				break;
			}
			for (auto i : m_vec[tmp]) {
				if (!visited[i]) {
					visited[i] = true;
					parents[i] = tmp;
					q.push(i);
				}
			}
		}
		int tmp = dest;
		if (parents[dest] == -1) {
			return {};
		}
		while (tmp != -1) {
			vec.push_back(tmp);
			tmp = parents[tmp];
		}
		std::reverse(vec.begin(), vec.end());
		return vec;
	}

	//for undirected graphs
	// bool Graph::hasCycle() const {
	// 	std::vector<bool> visited(m_vec.size(), false);
	// 	for (int i = 0; i < m_vec.size(); ++i) {
	// 		if (!visited[i] && hasCycleHelper(i, -1, visited)) {
	// 			return true;
	// 		}
	// 	}
	// 	return false;
	// }

	bool Graph::hasCycleHelper(int v, int parent, std::vector<bool>& visited) const {
		visited[v] = true;
		for (auto vec : m_vec[v]) {
			if (!visited[vec]) {
				if (hasCycleHelper(vec, v, visited)) {
					return true;
				}
			} else if (vec != parent) {
				return true;
			}
		}
		return false;
	}

	bool Graph::hasCycle() const {
		std::vector<bool> visited(m_vec.size(), false);
		std::vector<bool> inStack(m_vec.size(), false);
		for (int i = 0; i < m_vec.size(); ++i) {
			if (!visited[i] && hasCycleHelper(i, inStack, visited)) {
				return true;
			}
		}
		return false;
	}

	bool Graph::hasCycleHelper(int v, std::vector<bool>& inStack, std::vector<bool>& visited) const {
		visited[v] = true;
		inStack[v] = true;
		for (auto vec : m_vec[v]) {
			if (!visited[vec]) {
				if (hasCycleHelper(vec, inStack, visited)) {
					return true;
				}
			} else if (inStack[vec]) {
				return true;
			}
		}
		inStack[v] = false;
		return false;
	}

	std::vector<std::vector<int>> Graph::allPossiblePaths(int src, int dest) const {
		if (src >= m_vec.size() || dest >= m_vec.size()) {
			throw std::invalid_argument("The 'vertex' doesn't exist.");
		}
		std::vector<std::vector<int>> allPaths;
		std::vector<int> cur;
		allPossiblePathsHelper(src, dest, cur, allPaths);
		return allPaths;
	}

	void Graph::allPossiblePathsHelper(int src, int dest, std::vector<int>& cur, std::vector<std::vector<int>>& all) const {
		cur.push_back(src);
		if (src == dest) {
			all.push_back(cur);
		} else {
			for (auto& i : m_vec[src]) {
				allPossiblePathsHelper(i, dest, cur, all);
			}
		}
		cur.pop_back();
	}

	int Graph::countOfVertexesInLevel(int v, int level) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid index");
		}
		std::vector<bool> visited(m_vec.size(), false);
		std::queue<int> q;
		q.push(v);
		visited[v] = true;
		int curLevel = 0;
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; ++i) {
				int tmp = q.front();
				q.pop();
				for (auto& i : m_vec[tmp]) {
					if (!visited[i]) {
						q.push(i);
						visited[i] = true;
					}
				}
			}
			if (curLevel == level) {
				return size;
			}
			++curLevel;
		}
		throw std::invalid_argument("Level doesn't exist.");
	}



} // namespace DS
