#include "Stack.h"
#include <iostream>

Node::Node(int x) : x(x) {}

int Node::get_x() const {
    return x;
}

Node* Node::get_next() const {
    return next;
}

void Node::set_next(Node* node) { next = node; }

Stack::~Stack() {
    while (head != nullptr) {
        pop();
    }
}

int Stack::size() const {
    return sz;
}

bool Stack::empty() const {
    return sz == 0;
}

void Stack::push(int val) {
    Node* node = new Node(val);
    node->set_next(head);
    head = node;
    sz++;
}

void Stack::pop() {
    if (head == nullptr) {
        throw "Error in method pop: Impossible to call it if stack is empty";
    }
    Node* node = head;
    head = node->get_next();
    delete node;
    sz--;
}

int Stack::top() const {
    if (head == nullptr) {
        throw "Error in method top: Impossible to call it if stack is empty";
    }
    return head->get_x();
}

void Stack::print() const {
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->get_x() << ' ';
        cur = cur->get_next();
    }
}