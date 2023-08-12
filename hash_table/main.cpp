#include "hash_table.hpp"

#include <string>

int main() {
    DS::Hash_Table<std::string, int> mp {{"a", 0}};
    mp.max_load_factor(0.6);
    mp.insert(std::make_pair("h", 5));
    mp.insert(std::make_pair("e", 6));
    mp.insert(std::make_pair("l", 6));
    mp.insert(std::make_pair("l", 6));
    mp.insert(std::make_pair("o", 6));
    mp.insert(std::make_pair("o", 6));
    std::cout << "Hash_Table1 :" << std::endl << '\t';
    mp.print(); 
    std::cout << "Max load factor  -  " << mp.max_load_factor() << std::endl;
    std::cout << "Average load factor  -  " << mp.load_factor() << std::endl;
    mp.insert(std::make_pair("ff", 6));
    mp["ff"] = 2;
    mp["b"] = 11;
    mp.erase("l");
    std::cout << "Hash_Table1 :" << std::endl << '\t';
    mp.print();
    std::cout << "Hash_Table1 contains 'h'  -  " << std::boolalpha << mp.contains("h") << std::endl;
    mp.clear();
    std::cout << "Hash_Table1 is empty   -  " << std::boolalpha << mp.empty() << std::endl;
    std::cout << "Hash_Table1 contains 'h'  -  " << std::boolalpha << mp.contains("h") << std::endl;
    auto mp2(mp);
    mp2.insert({{"A", 3}, {"B", 2}, {"C", 1}});
    std::cout << "Hash_Table2 :" << std::endl << '\t';
    mp2.print();
    std::cout << "Size of Hash_Table2   -   " << mp2.size() << std::endl;
}