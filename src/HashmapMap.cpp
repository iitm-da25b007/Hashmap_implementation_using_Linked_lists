template <size_t N, typename KeyType, typename ValueType, typename HashFunc>
class HashMap{
public:
    HashMap() = default;
    ~HashMap() = default;

    HashMap &operator=(const HashMap &other) {
        if (this == &other) {
            return *this; // self assignment check
        }
        for (size_t i = 0;i < N;i++) {
            buckets[i] = other.buckets[i]; // copying bucket by bucket
        }
        n = other.n; // copying size
        return *this;
    }
    HashMap &operator=(HashMap &&other) noexcept {
        if (this == &other) {
            return *this; // self assignment check
        }
        for (size_t i = 0;i < N;i++) {
            buckets[i] = std::move(other.buckets[i]); // moving bucket by bucket
        }
        n = other.n; // copying size
        other.n = 0; // emptying given(other) hashmap
        return *this;
    }

    void insert(const KeyType &key, const ValueType &value) {
        size_t index = hash(key) % N; // computing bucket index
        if (!buckets[index].contains(key)) { // checking whether key already exists or not
            buckets[index].insert(key,value); // if not, inserting it delegately
            n++;
        }
    }
    void erase(const KeyType &key) {
        size_t index = hash(key) % N; // computing bucket index
        if (buckets[index].contains(key)) { // checking whether key already exists or not
            buckets[index].erase(key); // delegate erasing of key from bucket(linked list)
            n--;
        }
    }
    void clear() {
        for (size_t i = 0;i < N;i++) {
            buckets[i].clear(); // clearing bucket by bucket
        }
        n = 0; // resetting size
    }

    const ValueType &at(const KeyType &key) const {
        size_t index = hash(key) % N;
        return buckets[index].at(key); // delegate search of value for given key in bucket(linked list)
    }
    ValueType &at(const KeyType &key) {
        size_t index = hash(key) % N;
        return buckets[index].at(key); // delegate search of value for given key in bucket(linked list)
    }
    ValueType &operator[](const KeyType &key) {
        size_t index = hash(key) % N;
        if (!buckets[index].contains(key)) {
            buckets[index].insert(key,ValueType{}); // if not, inserting default value to it
            n++;
        }
        return buckets[index].at(key); // returning reference to value for given key
    }

    bool operator==(const HashMap &other) const {
        if (n != other.n) {
            return false; // size check
        }
        for (size_t i = 0;i < N;i++) {
            if (buckets[i] != other.buckets[i]) {
                return false; // comparing bucket by bucket
            }
        }
        return true;
    }
    bool operator!=(const HashMap &other) const {
        return !(*this == other);
    }

    [[nodiscard]] bool contains(const KeyType &key) const {
        size_t index = hash(key) % N; // computing bucket index
        return buckets[index].contains(key); // delegate search of key in corresponding bucket(linked list)
    }
    [[nodiscard]] bool empty() const {
        return (n == 0);
    }
    [[nodiscard]] size_t size() const {
        return n;
    }

private:
    HashFunc hash;
    using Bucket = LinkedList<KeyType, ValueType>;
    Bucket buckets[N];
    size_t n = 0;
};

template<typename T>
class HashFunctor{
public:
    size_t operator()(T Key) const;
};
// specialization for int
template<>
size_t HashFunctor<int>::operator()(int Key) const {
    return static_cast<size_t>(Key >= 0 ? Key : -Key); // direct conversion
}
// specialization for float
template<>
size_t HashFunctor<float>::operator()(float Key) const {
    float temp = Key * 1000; // multiplying by 1000 to preserve decimal information
    if (temp < 0) {
        temp = -temp;
    }
    return static_cast<size_t>(temp);
}
// specialization for string
template<>
size_t HashFunctor<std::string>::operator()(std::string Key) const {
    size_t hash = 0; // initializing hash value
    // traversing every character in string
    for (char c : Key) {
      // updating hash using polynomial rolling method
      // 31 is commonly used in string hashing
      hash = hash * 31 + static_cast<size_t>(c);
    }
    return hash;
}
