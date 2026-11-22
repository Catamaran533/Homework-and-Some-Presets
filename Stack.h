class Node {
private:
    int x;
    Node* next = nullptr;

public:
    Node(int x);
    int get_x() const;
    Node* get_next() const;
    void set_next(Node* node);
};

class Stack {
private:
    Node* head = nullptr;
    int sz = 0;

public:
    Stack() = default;
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    ~Stack();

    int size() const;
    bool empty() const;
    void push(int val);
    void pop();
    int top() const;
    void print() const;
};