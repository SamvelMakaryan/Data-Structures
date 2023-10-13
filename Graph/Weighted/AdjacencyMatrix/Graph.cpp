#include "Graph.hpp"

namespace DS {

    Graph::Graph(int v)
    : m_vec(v, std::vector<double>(v, std::numeric_limits<double>::infinity())),
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
        m_vec.push_back(std::vector<double>(m_vec.size() + 1, std::numeric_limits<double>::infinity()));
    }

    void Graph::addEdge(int src, int dest, double weight) {
        if (src >= m_vec.size() || dest >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex.");
        }
        if (std::isinf(m_vec[src][dest])) {
            m_vec[src][dest] = weight;
            ++m_edge_count;
        }
        //for undirected Graphs
        // if (std::isinf(m_vec[dest][src])) {
            // m_vec[dest][src] = weight;
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
        if (!std::isinf(m_vec[src][dest])) {
            m_vec[src][dest] = std::numeric_limits<double>::infinity();
            --m_edge_count;
        }
        //for undirected Graphs
        // if (!std::isinf(m_vec[dest][src])) {
        //     m_vec[dest][src] = std::numeric_limits<double>::infinity();
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
                if (!std::isinf(m_vec[tmp][i]) && !visited[i]) {
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
                    if (!std::isinf(m_vec[tmp][i]) && !visited[i]) {
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
			if (!std::isinf(m_vec[v][i]) && !visited[i]) {
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

    //for undirected graphs
    // bool Graph::hasCycle() const {
    //     std::vector<bool> visited(m_vec.size(), false);
    //     for (int i = 0; i < m_vec.size(); ++i) {
    //         if (!visited[i] && hasCycleHelper(i, -1, visited)) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }

    bool Graph::hasCycleHelper(int v, int parent, std::vector<bool>& visited) const {
        visited[v] = true;
        for (int i = 0; i < m_vec.size(); ++i) {
            if (!std::isinf(m_vec[v][i])) {
                if (!visited[i]) {
                    if (hasCycleHelper(i, v, visited)) {
                        return true;
                    } 
                } else if (i != parent) {
                    return true;
                }
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
        for (int i = 0; i < m_vec.size(); ++i) {
            if (!std::isinf(m_vec[v][i])) {
                if (!visited[i]) {
                    if (hasCycleHelper(i, inStack, visited)) {
                        return true;
                    } 
                } else if (inStack[i]) {
                    return true;
                }
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
            for (int i = 0; i < m_vec.size(); ++i) {
                if (!std::isinf(m_vec[src][i])) {
                    allPossiblePathsHelper(i, dest, cur, all);
                }
            }
        }
        cur.pop_back();
    }

    int Graph::countOfVertexesInLevel(int v, int level) const {
        if (v >= m_vec.size()) {
            throw std::invalid_argument("Invalid vertex.");
        }
        std::queue<int> q;
        std::vector<bool> visited(m_vec.size(), false);
        q.push(v);
        visited[v] = true;
        int curLevel = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int tmp = q.front();
                q.pop();
                for (int i = 0; i < m_vec.size(); ++i) {
                    if (!std::isinf(m_vec[tmp][i]) && !visited[i]) {
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


	std::vector<int> Graph::topologicalSort() const {
		if (m_vec.empty()) {
			return {};
		}
		std::vector<bool> visited(m_vec.size(), false);
		std::list<int> l;
		for (int i = 0; i < m_vec.size(); ++i) {
			if (!visited[i]) {
				topologicalSortHelper(i, visited, l);
			}
		}
		return std::vector<int>(l.begin(), l.end());
	}

	void Graph::topologicalSortHelper(int v, std::vector<bool>& visited, std::list<int>& l) const {
		visited[v] = true;
		for (int i = 0; i < m_vec.size(); ++i) {
			if (!std::isinf(m_vec[v][i]) && !visited[i]) {
				topologicalSortHelper(i, visited, l);
			}
		}
		l.push_front(v);
	}

    std::vector<std::vector<int>> Graph::getStronglyConnectedComponents() const {
		std::vector<int> ids(m_vec.size(), -1);
		std::vector<int> low(m_vec.size(), -1);
		std::vector<bool> inStack(m_vec.size(), false);
		std::vector<std::vector<int>> result;
		std::stack<int> s;
		int id = 0;
		for (int i = 0; i < m_vec.size(); ++i) {
			if (ids[i] == -1) {
				stronglyConnectedComponentsHelper(i, ids, low, inStack, s, result, id);
			}
		}
		return result;
	}
	
	void Graph::stronglyConnectedComponentsHelper(int v, std::vector<int>& ids, std::vector<int>& low, std::vector<bool>& inStack, 
													std::stack<int>& s, std::vector<std::vector<int>>& result, int& id) const {
		ids[v] = id;
		low[v] = id++;
		inStack[v] = true;
		s.push(v);
		for (int i = 0; i < m_vec.size(); ++i) {
			if (!std::isinf(m_vec[v][i])) {
                if (ids[i] == -1) {
                    stronglyConnectedComponentsHelper(i, ids, low, inStack, s, result, id);
                }
                if (inStack[i]) {
                    low[v] = std::min(low[v], low[i]); 
                }
            }
		}
		if (low[v] == ids[v]) {
			std::vector<int> cur;
			int tmp;
			do {
				tmp = s.top();
				s.pop();
				inStack[tmp] = false;
				cur.push_back(tmp);
			} while (tmp != v);
			result.push_back(cur);
		}
	}

    std::vector<double> Graph::singleSourceSHortestPath(int src) const {
		std::vector<double> distance(m_vec.size(), std::numeric_limits<double>::infinity());
		distance[src] = 0;
		auto comparator = [](const auto& p1, const auto& p2){return p1.first < p2.first;};
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comparator)> pq(comparator);
		pq.push({src, 0}); 
		while (!pq.empty()) {
			auto [v, w] = pq.top();
			pq.pop();
			if (w > distance[v]) {
				continue;
			}
			for (int i = 0; i < m_vec.size(); ++i) {
				if (!std::isinf(m_vec[v][i]) && distance[v] + m_vec[v][i] < distance[i]) {
					distance[i] = distance[v] + m_vec[v][i];
					pq.push({i, distance[i]});
				}
			}
		}
		return distance;
	}

} //namespace DS
