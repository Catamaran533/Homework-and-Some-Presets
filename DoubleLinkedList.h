#include <bits/stdc++.h>
using namespace std;


class Node {
private:
    int x;
    Node* prev = nullptr;
    Node* next = nullptr;

public:
    Node(int x) {
        this->x = x;
    }

    int get_x() {
        return x;
    }

    Node* get_prev() {
        return prev;
    }

    Node* get_next() {
        return next;
    }

    void set_prev(Node* node) {
        prev = node;
    }

    void set_next(Node* node) {
        next = node;
    }
};


class List {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    int sz = 0;

    Node* find1(int val) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->get_x() == val) {
                return cur;
            }
            cur = cur->get_next();
        }
        return nullptr;
    }

public:
    int size() {
        return sz;
    }

    bool empty() {
        return sz == 0;
    }

    void push_back(int val) {
        Node* node = new Node(val);
        node->set_prev(tail);
        if (tail == nullptr) {
            head = node;
        } else {
            tail->set_next(node);
        }
        tail = node;
        sz++;
    }

    void push_front(int val) {
        Node* node = new Node(val);
        node->set_next(head);
        if (head == nullptr) {
            tail = node;
        } else {
            head->set_prev(node);
        }
        head = node;
        sz++;
    }

    void pop_back() {
        if (tail == nullptr) {
            return;
        }
        Node* node = tail;
        tail = node->get_prev();
        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->set_next(nullptr);
        }
        delete node;
        sz--;
    }

    void pop_front() {
        if (head == nullptr) {
            return;
        }
        Node* node = head;
        head = node->get_next();
        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->set_prev(nullptr);
        }
        delete node;
        sz--;
    }

    void erase(int val) {
        Node* node = find1(val);
        if (node == nullptr) {
            return;
        }
        Node* p = node->get_prev();
        Node* n = node->get_next();
        if (p != nullptr) {
            p->set_next(n);
        } else {
            head = n;
        }
        if (n != nullptr) {
            n->set_prev(p);
        } else {
            tail = p;
        }
        delete node;
        sz--;
    }

    bool contains(int val) {
        return find1(val) != nullptr;
    }

    int front() {
        return head->get_x();
    }

    int back() {
        return tail->get_x();
    }

    void print() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->get_x() << ' ';
            cur = cur->get_next();
        }
    }

    ~List() {
        while (head != nullptr) {
            pop_front();
        }
    }
};