#pragma once
#include "SegTree.h"

template<typename Elem, typename Promise>
template<typename t>
SegTree<Elem, Promise>::SegTree(const std::vector<t>& b) {
    if (b.empty()) {
        throw "Error in constructor of SegTree: Impossible to create it if vector is empty";
    }
    n = b.size();
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
    tree.resize(4 * n);
    p.resize(4 * n);
    have_p.resize(4 * n);
    build(0, 0, n);
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * v + 1, l, mid);
    build(2 * v + 2, mid, r);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::update_promise(int v, Promise new_p) {
    if constexpr (available_promise) {
        if (have_p[v] == false) {
            p[v] = new_p;
            have_p[v] = true;
        } else {
            p[v].update(new_p);
        }
    }
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::do_promise(int v) {
    if constexpr (available_promise) {
        if (have_p[v] == false) {
            return;
        }
        tree[v].update(p[v]);
        have_p[v] = false;
    }
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::push(int v, int l, int r) {
    if constexpr (available_promise) {
        if (l + 1 == r) {
            do_promise(v);
            return;
        }
        if (have_p[v]) {
            update_promise(2 * v + 1, p[v]);
            update_promise(2 * v + 2, p[v]);
            do_promise(v);
        }
    }
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::update(int v, int l, int r, int ask_l, int ask_r, Promise new_p) {
    push(v, l, r);
    if (ask_l <= l and r <= ask_r) {
        update_promise(v, new_p);
        push(v, l, r);
        return;
    }
    if (r <= ask_l or ask_r <= l) {
        return;
    }
    int mid = (l + r) / 2;
    update(2 * v + 1, l, mid, ask_l, ask_r, new_p);
    update(2 * v + 2, mid, r, ask_l, ask_r, new_p);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

template<typename Elem, typename Promise>
std::pair<bool, Elem> SegTree<Elem, Promise>::merge(const std::pair<bool, Elem>& pa, const std::pair<bool, Elem>& pb) const {
    if (pa.first == false) {
        return pb;
    }
    if (pb.first == false) {
        return pa;
    }
    return {true, pa.second + pb.second};
}

template<typename Elem, typename Promise>
std::pair<bool, Elem> SegTree<Elem, Promise>::get(int v, int l, int r, int ask_l, int ask_r) {
    push(v, l, r);
    if (ask_l <= l and r <= ask_r) {
        return {true, tree[v]};
    }
    if (r <= ask_l or ask_r <= l) {
        return {false, Elem()};
    }
    int mid = (l + r) / 2;
    return merge(get(2 * v + 1, l, mid, ask_l, ask_r), get(2 * v + 2, mid, r, ask_l, ask_r));
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::set(int v, int l, int r, int idx, Elem val) {
    push(v, l, r);
    if (l + 1 == r) {
        tree[v] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (idx < mid) {
        set(2 * v + 1, l, mid, idx, val);
    } else {
        set(2 * v + 2, mid, r, idx, val);
    }
    push(2 * v + 1, l, mid);
    push(2 * v + 2, mid, r);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::update(int ask_l, int ask_r, Promise new_p) {
    if (ask_l < 0 or ask_r > n or ask_l >= ask_r) {
        throw "Error in method update: Impossible to call it if segment is incorrect";
    }
    update(0, 0, n, ask_l, ask_r, new_p);
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::update(int idx, Promise new_p) {
    if (idx < 0 or idx >= n) {
        throw "Error in method update: Impossible to call it if index is out of range";
    }
    update(0, 0, n, idx, idx + 1, new_p);
}

template<typename Elem, typename Promise>
Elem SegTree<Elem, Promise>::get(int ask_l, int ask_r) {
    if (ask_l < 0 or ask_r > n or ask_l >= ask_r) {
        throw "Error in method get: Impossible to call it if segment is incorrect";
    }
    return get(0, 0, n, ask_l, ask_r).second;
}

template<typename Elem, typename Promise>
Elem SegTree<Elem, Promise>::get(int idx) {
    if (idx < 0 or idx >= n) {
        throw "Error in method get: Impossible to call it if index is out of range";
    }
    return get(0, 0, n, idx, idx + 1).second;
}

template<typename Elem, typename Promise>
void SegTree<Elem, Promise>::set(int idx, Elem val) {
    if (idx < 0 or idx >= n) {
        throw "Error in method set: Impossible to call it if index is out of range";
    }
    set(0, 0, n, idx, val);
}