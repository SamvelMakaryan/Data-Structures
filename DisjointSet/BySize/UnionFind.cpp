#include "UnionFind.hpp"

namespace DS {
    
    UnionFind::UnionFind(int size)
    :   m_parents(size),
        m_sizes(size, 1),
        m_count(size) 
    {
     std::iota(m_parents.begin(), m_parents.end(), 0);
    }

    int UnionFind::getComponentsCount() const {
        return m_count;
    }

    int UnionFind::getSize() const {
        return m_parents.size();
    }

    int UnionFind::find(int v) {
        int root = v;
        while (root != m_parents[root]) {
            root = m_parents[root];
        }
        while (v != root) {
            int next = m_parents[v];
            m_parents[v] = root;
            v = next;
        }
        return root;
    }

    void UnionFind::unify(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            --m_count;
            if (m_sizes[rootU] < m_sizes[rootV]) {
                m_parents[rootU] = rootV;
                m_sizes[rootV] += m_sizes[rootU];
            } else {
                m_parents[rootV] = rootU;
                m_sizes[rootU] += m_sizes[rootV]; 
            }
        }
    }

    bool UnionFind::inSameComponent(int u, int v) {
        return find(u) == find(v);
    }

} // namespace DS
