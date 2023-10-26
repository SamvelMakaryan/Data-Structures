#include "UnionFind.hpp"

namespace DS {
    
    UnionFind::UnionFind(int size)
    :   m_parents(size),
        m_ranks(size, 0),
        m_count(size) 
    {
     std::iota(m_parents.begin(), m_parents.end(), 0);
    }

    int UnionFind::getComponentsCount() const {
        return m_count;
    }

    int UnionFind::getSize() const {
        return m_ranks.size();
    }

    int UnionFind::find(int v) {
        if (v != m_parents[v]) {
            m_parents[v] = find(m_parents[v]);
        }
        return m_parents[v];
    }

    void UnionFind::unify(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            --m_count;
            if (m_ranks[rootU] < m_ranks[rootV]) {
                m_parents[rootU] = rootV;
            } else if (m_ranks[rootU] > m_ranks[rootV]) {
                m_parents[rootV] = rootU;
            } else {
                m_parents[rootV] = rootU;
                ++m_ranks[rootU]; 
            }
        }
    }

    bool UnionFind::inSameComponent(int u, int v) {
        return find(u) == find(v);
    }

} // namespace DS
