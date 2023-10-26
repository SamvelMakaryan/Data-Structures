#include <iostream>

#include "UnionFind.hpp"

int main() {
    DS::UnionFind ds(10);
    ds.unify(0, 1);
    ds.unify(2, 3);
    ds.unify(1, 2);
    ds.unify(4, 5);
    ds.unify(6, 7);
    ds.unify(8, 9);
    ds.unify(1, 6);
    std::cout << "Are 0 and 7 in the same set? " << (ds.inSameComponent(0, 7) ? "Yes" : "No") << std::endl;
    std::cout << "Are 3 and 8 in the same set? " << (ds.inSameComponent(3, 8) ? "Yes" : "No") << std::endl;
    std::cout << "Count of elemnts in set is  -  " << ds.getSize() << std::endl;
    std::cout << "Count of components in set is  -  " << ds.getComponentsCount() << std::endl;
}