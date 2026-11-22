class Node {
private:
    int x;
    Node* prev = nullptr;
    Node* next = nullptr;

public:
    Node(int x);

    int get_x() const;
    Node* get_prev() const;
    Node* get_next() const;
    void set_prev(Node* node);
    void set_next(Node* node);
};

class List {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int sz = 0;

    Node* find1(int val) const;

public:
    List() = default;
    List(const List&) = delete;
    List& operator=(const List&) = delete;
    ~List();

    int size() const;
    bool empty() const;
    void push_back(int val);
    void push_front(int val);
    void pop_back();
    void pop_front();
    void erase(int val);
    bool contains(int val) const;
    int front() const;
    int back() const;
    void print() const;
};