#include "List.h"
#include <iostream>

Node::Node(int x) {
    this->x = x;
}

int Node::get_x() const {
    return x;
}

Node* Node::get_prev() const {
    return prev;
}

Node* Node::get_next() const {
    return next;
}

void Node::set_prev(Node* node) {
    prev = node;
}

void Node::set_next(Node* node) {
    next = node;
}

Node* List::find1(int val) const {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->get_x() == val) {
            return cur;
        }
        cur = cur->get_next();
    }
    return nullptr;
}

List::~List() {
    while (head != nullptr) {
        pop_front();
    }
}

int List::size() const {
    return sz;
}

bool List::empty() const {
    return sz == 0;
}

void List::push_back(int val) {
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

void List::push_front(int val) {
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

void List::pop_back() {
    if (tail == nullptr) {
        throw "Error in method pop_back: Impossible to call it if list is empty";
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

void List::pop_front() {
    if (head == nullptr) {
        throw "Error in method pop_front: Impossible to call it if list is empty";
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

void List::erase(int val) {
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

bool List::contains(int val) const {
    return find1(val) != nullptr;
}

int List::front() const {
    if (head == nullptr) {
        throw "Error in method front: Impossible to call it if list is empty";
    }
    return head->get_x();
}

int List::back() const {
    if (tail == nullptr) {
        throw "Error in method back: Impossible to call it if list is empty";
    }
    return tail->get_x();
}

void List::print() const {
    Node* cur = head;
    while (cur != nullptr) {
        std::cout << cur->get_x() << ' ';
        cur = cur->get_next();
    }
}