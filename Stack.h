#include <bits/stdc++.h>
using namespace std;


class Node {
private:
    int x;
    Node* next = nullptr;

public:
    Node(int x) {
        this->x = x;
    }

    int get_x() {
        return x;
    }

    Node* get_next() {
        return next;
    }

    void set_next(Node* node) {
        next = node;
    }
};


class Stack {
private:
    Node* head = nullptr;
    int sz = 0;

public:
    int size() {
        return sz;
    }

    bool empty() {
        return sz == 0;
    }

    void push(int val) {
        Node* node = new Node(val);
        node->set_next(head);
        head = node;
        sz++;
    }

    void pop() {
        if (head == nullptr) {
            return;
        }
        Node* node = head;
        head = node->get_next();
        delete node;
        sz--;
    }

    int top() {
        return head->get_x();
    }

    void print() {
        Node* cur = head;
        while (cur != nullptr) {
            cout << cur->get_x() << ' ';
            cur = cur->get_next();
        }
    }

    ~Stack() {
        while (head != nullptr) {
            pop();
        }
    }
};