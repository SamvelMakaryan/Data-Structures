#include "Graph.hpp"

namespace DS {
	
	Graph::Graph(std::size_t count) 
	: m_vec(count) {}
	
	bool Graph::empty() const noexcept {
		return m_vec.empty();
	}

	std::size_t Graph::getEdgeCount() const noexcept {
		return m_edge_count;
	}	
	
	std::size_t Graph::getVertexCount() const noexcept {
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
		m_vec.push_back(std::forward_list<std::size_t>{});
	}
	
	
	void Graph::addEdge(std::size_t src, std::size_t dest) {
		if (dest >= m_vec.size()) {
			throw std::invalid_argument("The 'edge' should connect consisting elements.");
		}	
		++m_edge_count;
		m_vec[src].emplace_front(dest);
		//for undirected
		//m_vec[dest].emplace_front(src);
		//++m_edge_count;
	}

		
	
	void Graph::removeEdge(std::size_t src, std::size_t dest) {
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

	void Graph::removeVertex(std::size_t v) {
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
		
	void Graph::BFS(std::size_t v) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		std::vector<bool> visited(m_vec.size(), false);
		std::queue<std::size_t> q;
		q.push(v);
		visited[v] = true;
		while (!q.empty()) {
			std::size_t size = q.size();
			while (size--) {
				std::size_t tmp = q.front();
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

	void Graph::extraDFS(std::size_t v) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		std::vector<bool> visited(m_vec.size(), false);
		long ver = v;
		while (ver != -1) {
			extraDFSHelper(ver, visited, true);
			ver = is_visted(visited);
		}
		std::cout << std::endl;
	}

	void Graph::extraDFSHelper(std::size_t v, std::vector<bool>& visited, bool print) const {
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

	long Graph::is_visted(std::vector<bool>& vec) const {
		for (int i = 0; i < vec.size(); ++i) {
			if (!vec[i]) {
				return i;
			}
		}
		return -1;
	}

	std::size_t Graph::getCountOfComponents() const {
		if (m_vec.empty()) {
			return 1;
		}
		std::size_t components = 0;
		std::vector<bool> visited(m_vec.size(), false);
		long ver = 0;
		while (ver != -1) {
			++components;
			extraDFSHelper(ver, visited, false);
			ver = is_visted(visited);
		}
		return components;
	}

	void Graph::DFS(std::size_t v) const {
		if (v >= m_vec.size()) {
			throw std::invalid_argument("Invalid vertex.");		
		}
		std::vector<bool> visited(m_vec.size(), false);
		std::stack<std::size_t> s;
		s.push(v);
		visited[v] = true;
		while (!s.empty()) {
			std::size_t tmp = s.top();
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
	
} // namespace DS
