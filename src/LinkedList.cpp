template <typename KeyType, typename ValueType>
class LinkedList{
public:
    LinkedList() {
        head = nullptr;
        n = 0;
    }
    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList &other);
    LinkedList(LinkedList &&other) noexcept;
    LinkedList &operator=(const LinkedList &other);
    LinkedList &operator=(LinkedList &&other) noexcept;

    void insert(const KeyType &key, const ValueType &value) {
        ValueType *ptr = find(key); // checking if given key is already there or not
        if (ptr!=nullptr) {
            *ptr = value; // if present, updating its value
            return;
        }
        Node *newNode = new Node{key, value, head}; // creating new node
        head = newNode; // making it head
        n++; // increasing size
    }
    void erase(const KeyType &key) {
        Node *curr = head; // initializing pointer node
        if (curr==nullptr) {
            return; // check for empty linked list
        }
        // For removing head node
        if (curr->key == key){
            head = head->next; // changing head to its next node
            delete curr; // deleting head node(i.e. curr)
            n--; // decreasing size
            return;
        }
        // For removing non-head node
        while (curr->next!=nullptr) {
           if (curr->next->key==key) {
             Node *temp = curr->next; // creating temporary node as our required node
             curr->next = curr->next->next; // changing previous node's next to required node's next node
             delete temp; // deleting required node
             n--; // decreasing size
             return;
           }
           curr = curr->next; // transvering list
        }
    }

    void clear() {
      while (head!=nullptr) {
         Node *temp = head; // initializing temporary node as head
         head = head->next; // changing head to its next node
         delete temp; // deleting previous head node(i.e. temporary node)
      }
      n=0; // making size of list zero
    }

    const ValueType &at(const KeyType &key) const {
        const ValueType *ptr = find(key); // address of value for given key
        if (ptr==nullptr) {
            throw std::out_of_range("Key not found"); // checking if key is in list or not
        }
        return *ptr; // returns value at that address
    }
    ValueType &at(const KeyType &key){
        ValueType *ptr = find(key); // address of value for given key
        if (ptr==nullptr) {
            throw std::out_of_range("Key not found"); // checking if key is in list or not
        }
        return *ptr; // returns value at that address
    }
    ValueType *find(const KeyType &key) {
        Node *curr = head; // initializing pointer node
        while (curr!=nullptr) {
            if (curr->key == key) {
            return &(curr->value); // if matches, returns its address
            }
            curr = curr->next;  // transversing the list
        }
        return nullptr; // if not found
    }
    const ValueType *find(const KeyType &key) const {
        const Node *curr = head; // initializing pointer node
        while (curr!=nullptr) {
            if (curr->key == key) {
            return &(curr->value); // if matches, returns its address
            }
            curr = curr->next; // transversing the list
        }
        return nullptr; // if not found
    }

    bool operator==(const LinkedList &other) const;
    bool operator!=(const LinkedList &other) const;

    [[nodiscard]] bool contains(const KeyType &key) const {
        return (find(key) != nullptr); // If key is there, we will get some value(means list contains that key)
    }
    [[nodiscard]] size_t size() const {
        return n; // gives current size of linked list
    }

private:
    struct Node{
        KeyType key;
        ValueType value;
        Node *next;
    };
    Node *head = nullptr;
    size_t n = 0;
};
