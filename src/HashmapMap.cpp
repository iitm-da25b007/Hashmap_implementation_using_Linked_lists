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
