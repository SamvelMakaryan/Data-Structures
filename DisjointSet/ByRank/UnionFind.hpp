#ifndef UNIONFIND_HPP_
#define UNIONFIND_HPP_

#include <numeric>
#include <vector>

namespace DS {
    
    class UnionFind {
    public:
        UnionFind(int);
        UnionFind(const UnionFind&) = default;
        UnionFind(UnionFind&&) noexcept = default;
        ~UnionFind() = default;
    public:
        int find(int);
        void unify(int, int);
        int getComponentsCount() const;
        int getSize() const;
        bool inSameComponent(int, int);
    private:
        std::vector<int> m_ranks;
        std::vector<int> m_parents;
        int m_count;
    };

} // namespace DS

#endif //UNIONFIND_HPP_