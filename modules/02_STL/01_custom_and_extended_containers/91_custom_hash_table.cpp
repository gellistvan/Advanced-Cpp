#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <stdexcept>

template <typename Key, typename Value>
class HashTable {
public:
    explicit HashTable(std::size_t bucket_count = 16);

    void insert(const Key& key, const Value& value);
    void remove(const Key& key);
    Value& get(const Key& key);
    const Value& get(const Key& key) const;
    bool contains(const Key& key) const;

private:
    std::vector<std::list<std::pair<Key, Value>>> buckets;
    std::hash<Key> hash_function;

    std::size_t get_bucket_index(const Key& key) const;
};

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(std::size_t bucket_count) : buckets(bucket_count) {}

template <typename Key, typename Value>
std::size_t HashTable<Key, Value>::get_bucket_index(const Key& key) const {
    return hash_function(key) % buckets.size();
}

template <typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value) {
    std::size_t bucket_index = get_bucket_index(key);
    for (auto& pair : buckets[bucket_index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    buckets[bucket_index].emplace_back(key, value);
}

template <typename Key, typename Value>
void HashTable<Key, Value>::remove(const Key& key) {
    std::size_t bucket_index = get_bucket_index(key);
    auto& bucket = buckets[bucket_index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            return;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value>
Value& HashTable<Key, Value>::get(const Key& key) {
    std::size_t bucket_index = get_bucket_index(key);
    for (auto& pair : buckets[bucket_index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value>
const Value& HashTable<Key, Value>::get(const Key& key) const {
    std::size_t bucket_index = get_bucket_index(key);
    for (const auto& pair : buckets[bucket_index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Value>
bool HashTable<Key, Value>::contains(const Key& key) const {
    std::size_t bucket_index = get_bucket_index(key);
    for (const auto& pair : buckets[bucket_index]) {
        if (pair.first == key) {
            return true;
        }
    }
    return false;
}

int main() {
    HashTable<std::string, int> ht;

    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("three", 3);

    std::cout << "one: " << ht.get("one") << std::endl;
    std::cout << "two: " << ht.get("two") << std::endl;
    std::cout << "three: " << ht.get("three") << std::endl;

    ht.remove("two");

    if (!ht.contains("two")) {
        std::cout << "Key 'two' successfully removed" << std::endl;
    }

    return 0;
}