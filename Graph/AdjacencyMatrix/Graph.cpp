#include "Graph.hpp"

namespace DS {

    Graph::Graph(int v)
    : m_vec(v, std::vector<bool>(v, false)),
      m_edge_count(0) {}

    Graph& Graph::operator=(const Graph& oth) {
        if (this == &oth) {
            return *this;
        }
        m_vec = oth.m_vec;
        m_edge_count = oth.m_edge_count;
        return *this;
    }

    Graph& Graph::operator=(Graph&& oth) noexcept {
        if (this == &oth) {
            return *this;
        }
        m_vec = std::move(oth.m_vec);
        m_edge_count = oth.m_edge_count;
        return *this;
    }

    void Graph::addVertex() {
        m_vec.push_back(std::vector<bool>(m_vec.size() + 1, false));
    }

    void Graph::addEdge(int src, int dest) {
        if (src >= m_vec.size() || dest >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex.");
        }
        if (!m_vec[src][dest]) {
            m_vec[src][dest] = true;
            ++m_edge_count;
        }
        //for undirected Graphs
        // if (!m_vec[dest][src]) {
            // m_vec[dest][src] = true;
            // ++m_edge_count;
        // }
    }

    int Graph::getEdgeCount() const noexcept {
        return m_edge_count;
    }

    int Graph::getVertexCount() const noexcept {
        return m_vec.size();
    }

    [[nodiscard]] bool Graph::empty() const noexcept {
        return m_vec.empty();
    }

    void Graph::clear() {
        m_vec.clear();
    }

    void Graph::removeVertex(int v) {
        if (v >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex.");
        }
        m_vec.erase(m_vec.begin(), m_vec.begin() + v);
        for (auto vec : m_vec) {
            vec.erase(vec.begin(), vec.begin() + v);
        }
    }

    void Graph::removeEdge(int src, int dest) {
        if (src >= m_vec.size() || dest >= m_vec.size()) {
            throw std::invalid_argument("Invalid edge.");
        }
        if (m_vec[src][dest]) {
            m_vec[src][dest] = false;
            --m_edge_count;
        }
        //for undirected Graphs
        // if (m_vec[dest][src]) {
        //     m_vec[dest][src] = false;
        //     --m_edge_count;
        // }
    }

    void Graph::transpose() {
        for (int i = 0; i < m_vec.size(); ++i) {
            for (int j = i + 1; j < m_vec.size(); ++j) {
                std::swap(m_vec[i][j], m_vec[j][i]);
            }
        }
    }

    void Graph::DFS(int v) const {
        if (v >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex");
        }
        std::stack<int> s;
        std::vector<bool> visited(m_vec.size(), false);
        s.push(v);
        visited[v] = true;
        while (!s.empty()) {
            int tmp = s.top();
            s.pop();
            std::cout << tmp << " ";
            for (int i = 0; i < m_vec.size(); ++i) {
                if (m_vec[tmp][i] == 1 && !visited[i]) {
                    s.push(i);
                    visited[i] = true;
                }
            }
        }
        std::cout << std::endl;
        
    }

    void Graph::BFS(int v) const {
        if (v >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex");
        }
        std::queue<int> q;
        std::vector<bool> visited(m_vec.size(), false);
        q.push(v);
        visited[v] = true;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                int tmp = q.front();
                q.pop();
                std::cout << tmp << " ";
                for (int i = 0; i < m_vec.size(); ++i) {
                    if (m_vec[tmp][i] == 1 && !visited[i]) {
                        q.push(i);
                        visited[i] = true;
                    }
                }
            }
            std::cout << std::endl;
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

    void Graph::extraDFS(int v) const {
        if (v >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex");
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
		for (int i = 0; i < m_vec.size(); ++i) {
			if (m_vec[v][i] && !visited[i]) {
				extraDFSHelper(i, visited, print);
			}
		}
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
			for (int i = 0; i < m_vec.size(); ++i) {
				if (m_vec[tmp][i] && !visited[i]) {
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
}
