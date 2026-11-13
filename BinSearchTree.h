#include <bits/stdc++.h>
using namespace std;


class Node {
private:
    int x;
    Node* l = nullptr;
    Node* r = nullptr;

    void insert1(int val) {
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

    pair<int, bool> get_second_max1(Node* root) {

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

        pair<int, bool> ans = get_second_max1(root->r);
        if (ans.second == true) {
            return {root->x, false};
        }
        return ans;
    }

public:
    Node(int x) {
        this->x = x;
    }

    void insert(int val) {
        insert1(val);
    }

    ~Node() {
        delete l;
        delete r;
    }

    int get_second_max() {
        return get_second_max1(this).first;
    }

};


class BinSearchTree {
private:
    Node* root = nullptr;
public:
    void insert(int val) {
        if (root == nullptr) {
            root = new Node(val);
        } else {
            root->insert(val);
        }
    }

    ~BinSearchTree() {
        delete root;
    }

    int get_second_max() {
        return root->get_second_max();
    }
};