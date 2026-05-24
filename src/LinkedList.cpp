template <typename KeyType, typename ValueType>
class LinkedList{
public:
    LinkedList() = default;
    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList &other) {
        head = nullptr;
        n=0;
        if (other.head == nullptr) {
            return; // checking whether given list is empty or not
        }
        const Node *curr = other.head; // initializing traversal pointer
        head = new Node{curr->key,curr->value,nullptr}; // copying first node at different address(i.e. new)
        Node *tail = head; // initializing new list's traversing pointer
        curr = curr->next;
        while (curr != nullptr) {
            tail->next = new Node{curr->key,curr->value,nullptr}; // copying remaining nodes
            tail = tail->next;
            curr = curr->next; // traversing
        }
        n = other.n; // updating size
    }
    LinkedList(LinkedList &&other) noexcept {
        head = other.head; // taking ownership of node chain(moving)
        n = other.n; // updating size
        other.head = nullptr; // making given list(i.e. other) to empty
        other.n = 0; // updating given list's size to zero
    }
    LinkedList &operator=(const LinkedList &other) {
        if (this==&other) {
            return *this; // self assignment check
        }
        clear(); // removing old nodes
        if (other.head == nullptr) {
            return *this; // empty list case
        }
        const Node *curr = other.head;
        head = new Node{curr->key,curr->value,nullptr}; // copying first node
        Node *tail = head;
        curr = curr->next;
        while (curr != nullptr) {
            tail->next = new Node{curr->key,curr->value,nullptr}; // copying remaining nodes
            tail = tail->next;
            curr = curr->next;
        }
        n = other.n; // updating size
        return *this;
    }
    LinkedList &operator=(LinkedList &&other) noexcept {
        if (this == &other) {
            return *this;  // self assignment check
        }
        clear(); // removing old nodes
        head = other.head; // transferring ownership
        n = other.n;
        other.head = nullptr; // emptying other
        other.n = 0;
        return *this;
    }

    void insert(const KeyType &key, const ValueType &value) {
        if (contains(key)) {
            return; // checking whether key already exists or not
        }
        Node *newNode = new Node{key, value, head}; // creating new node
        head = newNode; // making it head
        n++; // increasing size
    }
    void erase(const KeyType &key) {
        Node *curr = head; // initializing pointer node
        if (curr == nullptr) {
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
        while (curr->next != nullptr) {
           if (curr->next->key == key) {
             Node *temp = curr->next; // creating temporary node as our required node
             curr->next = curr->next->next; // changing previous node's next to required node's next node
             delete temp; // deleting required node
             n--; // decreasing size
             return;
           }
           curr = curr->next; // traversing list
        }
    }

    void clear() {
      while (head != nullptr) {
         Node *temp = head; // initializing temporary node as head
         head = head->next; // changing head to its next node
         delete temp; // deleting previous head node(i.e. temporary node)
      }
      n=0; // making size of list zero
    }

    const ValueType &at(const KeyType &key) const {
        const ValueType *ptr = find(key); // address of value for given key
        if (ptr == nullptr) {
            throw std::out_of_range("Key not found"); // checking if key is in list or not
        }
        return *ptr; // returns value at that address
    }
    ValueType &at(const KeyType &key){
        ValueType *ptr = find(key); // address of value for given key
        if (ptr == nullptr) {
            throw std::out_of_range("Key not found"); // checking if key is in list or not
        }
        return *ptr; // returns value at that address
    }
    ValueType *find(const KeyType &key) {
        Node *curr = head; // initializing pointer node
        while (curr != nullptr) {
            if (curr->key == key) {
            return &(curr->value); // if matches, returns its address
            }
            curr = curr->next;  // traversing the list
        }
        return nullptr; // if not found
    }
    const ValueType *find(const KeyType &key) const {
        const Node *curr = head; // initializing pointer node
        while (curr != nullptr) {
            if (curr->key == key) {
            return &(curr->value); // if matches, returns its address
            }
            curr = curr->next; // traversing the list
        }
        return nullptr; // if not found
    }

    bool operator==(const LinkedList &other) const {
        if (n != other.n) {
           return false; // size check
        }
        const Node *curr = head;  // initializing traversal nodes
        while (curr != nullptr) {
            const ValueType *ptr = other.find(curr->key);
            if (ptr == nullptr) {
                return false; // checking whether our required key exists or not
            }
            if (*ptr != curr->value) {
                return false; // checking value of that corresponding key
            }
            curr = curr->next; // traversing the list
        }
        return true;
    }
    bool operator!=(const LinkedList &other) const {
        return !(*this == other); // reversing answer of equality checker
    }

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
