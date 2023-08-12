#ifndef HASH_TABLE_HPP_
#define HASH_TABLE_HPP_

#include <initializer_list>
#include <forward_list>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

namespace DS {
    
    template <typename Key, typename Value>
    class Hash_Table {
    public:
        using size_type = std::size_t;
        using value_type = std::pair<const Key, Value>;
    private:
        static constexpr const size_type default_size = 17;
        static constexpr const float default_load_factor = 0.75f;
    public:
        explicit Hash_Table(size_type = default_size);
        Hash_Table(const Hash_Table&);
        Hash_Table(Hash_Table&&) noexcept;
        Hash_Table(std::initializer_list<value_type>);
        ~Hash_Table() = default;
    public:
        Hash_Table& operator=(const Hash_Table&);
        Hash_Table& operator=(Hash_Table&&) noexcept;
        Value& operator[](const Key&);
    public:
        size_type size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        bool contains(const Key&) const;
        void insert(const value_type&);
        void insert(value_type&&);
        void insert(std::initializer_list<value_type>);
        void clear() noexcept;
        void erase(const Key&);
        float load_factor() const;
        float max_load_factor() const;
        void max_load_factor(float);
        void print() const;
    private:
        size_type hash_function(const Key&) const;
        void rehash();
    private:
        std::vector<std::forward_list<value_type>> m_table;
        size_type m_size;
        float m_load_factor;
    };

} //DS namespace

#include "hash_table.tpp"

#endif //HASH_TABLE_HPP_
