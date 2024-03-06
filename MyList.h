template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T data) {
        this->data = data;
        this->next = nullptr;
    }
};

template<typename T>
class List {
public:
    Node<T>* first_node;
    Node<T>* last_node;

    List() : first_node(nullptr), last_node(nullptr) {}

    class Iterator {
    public:
        Node<T>* current_node;

        Iterator(Node<T>* node) : current_node(node) {}

        Iterator& operator++() {
            current_node = current_node->next;
            return *this;
        }

        T& operator*() {
            return current_node->data;
        }

        bool operator!=(const Iterator& other) {
            return current_node != other.current_node;
        }

        T* operator->() {
            return &(current_node->data);
        }

        const T* operator->() const {
            return &(current_node->data);
        }
    };

    Iterator begin() {
        return Iterator(first_node);
    }

    const Iterator begin() const{
        return Iterator(first_node);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    const Iterator end() const {
        return Iterator(nullptr);
    }

    void push_back(T data) {
        Node<T>* new_node = new Node<T>(data);
        if (last_node) {
            last_node->next = new_node;
            last_node = new_node;
        }
        else {
            first_node = last_node = new_node;
        }
    }

    /*void erase(Iterator iter) {
        if (first_node == nullptr || iter.current_node == nullptr) {
            throw std::runtime_error("Invalid iterator or empty list");
        }

        if (iter.current_node == first_node) {
            Node<T>* to_delete = first_node;
            first_node = first_node->next;
            delete to_delete;
            return;
        }

        Node<T>* node = first_node;
        while (node->next && node->next != iter.current_node) {
            node = node->next;
        }

        if (node->next == iter.current_node) {
            Node<T>* to_delete = node->next;
            node->next = node->next->next;
            delete to_delete;
        }
    }*/
    Iterator erase(Iterator iter) {
        if (first_node == nullptr || iter.current_node == nullptr) {
            throw std::runtime_error("Invalid iterator or empty list");
        }

        if (iter.current_node == first_node) {
            Node<T>* to_delete = first_node;
            first_node = first_node->next;
            delete to_delete;
            return Iterator(first_node);
        }

        Node<T>* node = first_node;
        while (node->next && node->next != iter.current_node) {
            node = node->next;
        }

        if (node->next == iter.current_node) {
            Node<T>* to_delete = node->next;
            node->next = node->next->next;
            delete to_delete;
            return Iterator(node->next);
        }

        // If the element is not found, return the iterator end()
        return Iterator(nullptr);
    }

};


