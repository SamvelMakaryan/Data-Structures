#ifndef HASH_TABLE_TPP_
#define HASH_TABLE_TPP_

namespace DS {

    template <typename Key, typename Value>
    Hash_Table<Key, Value>::Hash_Table(size_type size)
    :   m_size(0),
        m_table(size),
        m_load_factor(default_load_factor) {}
    
    template <typename Key, typename Value>
    Hash_Table<Key, Value>::Hash_Table(const Hash_Table& oth) 
    :   m_size(oth.m_size),
        m_table(oth.m_table),
        m_load_factor(oth.m_load_factor) {}
    
    template <typename Key, typename Value>
    Hash_Table<Key, Value>::Hash_Table(Hash_Table&& oth) noexcept
    :   m_size(std::move(oth.m_size)),
        m_table(std::move(oth.m_table)),
        m_load_factor(std::move(oth.m_load_factor)) {}

    template <typename Key, typename Value>
    Hash_Table<Key, Value>::Hash_Table(std::initializer_list<value_type> init)
    :   Hash_Table()
    {
        insert(init);
    }

    template <typename Key, typename Value>
    Hash_Table<Key, Value>& Hash_Table<Key, Value>::operator=(const Hash_Table& rhs) {
        m_table = rhs.m_table;
        m_size = rhs.m_size;
        m_load_factor = rhs.m_load_factor;
        return *this;
    }

    template <typename Key, typename Value>
    Hash_Table<Key, Value>& Hash_Table<Key, Value>::operator=(Hash_Table&& rhs) noexcept {
        m_table = std::move(rhs.m_table);
        m_size = std::move(rhs.m_size);
        m_load_factor = std::move(rhs.m_load_factor);
        return *this;
    }

    template <typename Key, typename Value>
    typename Hash_Table<Key, Value>::size_type Hash_Table<Key, Value>::hash_function(const Key& key) const {
        return std::hash<Key>()(key) % m_table.size();
    }

    template <typename Key, typename Value>
    typename Hash_Table<Key, Value>::size_type Hash_Table<Key, Value>::size() const noexcept {
        return m_size;
    }

    template <typename Key, typename Value>
    [[nodiscard]] bool Hash_Table<Key, Value>::empty() const noexcept {
        return m_size == 0;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::clear() noexcept {
        for (auto& bucket : m_table) {
            bucket.clear();
        }
        m_size = 0;
    }

    template <typename Key, typename Value>
    bool Hash_Table<Key, Value>::contains(const Key& key) const {
        if (m_size != 0) {
            size_type index = hash_function(key);
            for (const auto& pair : m_table[index]) {
                if (pair.first == key) {
                    return true;
                }
            }
        }
        return false;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::insert(const value_type& val) {
        if (load_factor() >= m_load_factor) {
            rehash();
        }
        size_type index = hash_function(val.first);
        for (const auto& pair : m_table[index]) {
            if (pair.first == val.first) {
                return;
            }
        }
        m_table[index].push_front(val);
        ++m_size;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::insert(value_type&& val) {
        if (load_factor() >= m_load_factor) {
            rehash();
        }
        size_type index = hash_function(val.first);
        for (const auto& pair : m_table[index]) {
            if (pair.first == val.first) {
                return;
            }
        }
        m_table[index].push_front(std::move(val));
        ++m_size;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::insert(std::initializer_list<value_type> init) {
        for (const auto& i : init) {
            insert(i);
        }
    }
    
    template <typename Key, typename Value>
    Value& Hash_Table<Key, Value>::operator[](const Key& key) {
        if (load_factor() >= m_load_factor) {
            rehash();
        }
        size_type index = hash_function(key);
        for (auto& pair : m_table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        m_table[index].emplace_front(key, Value());
        ++m_size;
        return m_table[index].front().second;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::erase(const Key& key) {
        auto& bucket = m_table[hash_function(key)];
        auto prev = bucket.before_begin();
        bool deleted = false;
        for (auto it = bucket.begin(); it != bucket.end(); ++it, ++prev) {
            if (it->first == key) {
                deleted = true;
                bucket.erase_after(prev);
                break;
            }
        }
        if (deleted) {
            --m_size;
        }
    }

    template <typename Key, typename Value>
    float Hash_Table<Key, Value>::load_factor() const {
        return static_cast<float>(m_size) / m_table.size(); 
    }

    template <typename Key, typename Value>
    float Hash_Table<Key, Value>::max_load_factor() const {
        return m_load_factor;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::max_load_factor(float ml) {
        m_load_factor = ml;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::rehash() {
        Hash_Table<Key, Value> tmp(m_table.size() * 1.5);
        tmp.max_load_factor(m_load_factor);
        for (const auto& bucket : m_table) {
            for (const auto& pair : bucket) {
                tmp.insert(pair);
            }
        }
        *this = tmp;
    }

    template <typename Key, typename Value>
    void Hash_Table<Key, Value>::print() const {
        for (const auto& bucket : m_table) {
            for (const auto& pair : bucket) {
                std::cout << '[' << pair.first << ':' << pair.second << ']' << ' ';
            }
        }
        std::cout << std::endl;
    }

} //namespace DS

#endif //HASH_TABLE_TPP_