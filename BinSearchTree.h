#include <utility>

class Node {
private:
    int x;
    Node* l = nullptr;
    Node* r = nullptr;

    void insert1(int val);
    std::pair<int, bool> get_second_max1(Node* root);

public:
    Node(int x);
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    ~Node();

    void insert(int val);
    int get_second_max();
};

class BinSearchTree {
private:
    Node* root = nullptr;

public:
    BinSearchTree() = default;
    BinSearchTree(const BinSearchTree&) = delete;
    BinSearchTree& operator=(const BinSearchTree&) = delete;
    ~BinSearchTree();

    void insert(int val);
    int get_second_max();
};