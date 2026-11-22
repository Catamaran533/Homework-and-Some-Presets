#include "BinSearchTree.h"

Node::Node(int x) {
    this->x = x;
}

Node::~Node() {
    delete l;
    delete r;
}

void Node::insert1(int val) {
    if (x == val) {
        return;
    }
    if (val < x) {
        if (l == nullptr) {
            l = new Node(val);
        } else {
            l->insert1(val);
        }
    } else {
        if (r == nullptr) {
            r = new Node(val);
        } else {
            r->insert1(val);
        }
    }
}

std::pair<int, bool> Node::get_second_max1(Node* root) {
    if (root->r == nullptr) {
        if (root->l == nullptr) {
            return {0, true};
        }

        Node* m = root->l;
        while (m->r != nullptr) {
            m = m->r;
        }
        return {m->x, false};
    }

    std::pair<int, bool> ans = get_second_max1(root->r);
    if (ans.second == true) {
        return {root->x, false};
    }
    return ans;
}

void Node::insert(int val) {
    insert1(val);
}

int Node::get_second_max() {
    std::pair<int, bool> ans = get_second_max1(this);
    if (ans.second == true) {
        throw "Error in method get_second_max: Impossible to call it if tree has less than two elements";
    }
    return ans.first;
}

void BinSearchTree::insert(int val) {
    if (root == nullptr) {
        root = new Node(val);
    } else {
        root->insert(val);
    }
}

BinSearchTree::~BinSearchTree() {
    delete root;
}

int BinSearchTree::get_second_max() {
    if (root == nullptr) {
        throw "Error in method get_second_max: Impossible to call it if tree is empty";
    }
    return root->get_second_max();
}