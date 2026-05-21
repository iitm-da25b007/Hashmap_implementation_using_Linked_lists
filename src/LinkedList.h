template <typename KeyType, typename ValueType>
class LinkedList{
public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList &other);
    LinkedList(LinkedList &&other) noexcept;
    LinkedList &operator=(const LinkedList &other);
    LinkedList &operator=(LinkedList &&other) noexcept;

    void insert(const KeyType &key, const ValueType &value);
    void erase(const KeyType &key);
    void clear();

    const ValueType &at(const KeyType &key) const;
    ValueType &at(const KeyType &key);
    ValueType *find(const KeyType &key);

    bool operator==(const LinkedList &other) const;
    bool operator!=(const LinkedList &other) const;

    [[nodiscard]] bool contains(const KeyType &key) const;
    [[nodiscard]] size_t size() const;

private:
    struct Node{
        KeyType key;
        ValueType value;
        Node *next;
    };
    Node *head = nullptr;
    size_t n = 0;
};
