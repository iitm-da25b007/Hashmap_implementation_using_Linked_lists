#include <cstddef>
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

template <size_t N, typename KeyType, typename ValueType, typename HashFunc>
class HashMap{
public:
    HashMap();
    ~HashMap();

    HashMap &operator=(const HashMap &other);
    HashMap &operator=(HashMap &&other) noexcept;

    void insert(const KeyType &key, const ValueType &value);
    void erase(const KeyType &key);
    void clear();

    const ValueType &at(const KeyType &key) const;
    ValueType &at(const KeyType &key);
    ValueType &operator[](const KeyType &key);

    bool operator==(const HashMap &other) const;
    bool operator!=(const HashMap &other) const;

    [[nodiscard]] bool contains(const KeyType &key) const;
    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;

private:
    HashFunc hash;
    using Bucket = LinkedList<KeyType, ValueType>;
    Bucket buckets[N];
};

template<typename T>
class HashFunctor{
public:
    size_t operator()(T Key) const;
};
