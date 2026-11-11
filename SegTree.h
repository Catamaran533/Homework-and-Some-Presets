#include <vector>
using namespace std;

class DefaultPromise {};

template<typename Elem, typename Promise = DefaultPromise>
class SegTree {
private:
    int n;
    vector<Elem> a;
    vector<Elem> tree;
    vector<Promise> p;
    vector<bool> have_p;

    static constexpr bool available_promise = not is_same_v<Promise, DefaultPromise>;

    void build(int v, int l, int r) {
        if (l + 1 == r) {
            tree[v] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * v + 1, l, mid);
        build(2 * v + 2, mid, r);
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }

    void update_promise(int v, Promise new_p) {
        if constexpr (available_promise) {
            if (have_p[v] == false) {
                p[v] = new_p;
                have_p[v] = true;
            } else {
                p[v].update(new_p);
            }
        }
    }

    void do_promise(int v) {
        if constexpr (available_promise) {
            if (have_p[v] == false) {
                return;
            }
            tree[v].update(p[v]);
            have_p[v] = false;
        }
    }

    void push(int v, int l, int r) {
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

    void update(int v, int l, int r, int ask_l, int ask_r, Promise new_p) {
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

    pair<bool, Elem> merge (const pair<bool, Elem>& pa, const pair<bool, Elem>& pb) const {
        if (pa.first == false) {
            return pb;
        }
        if (pb.first == false) {
            return pa;
        }
        return {true, pa.second + pb.second};
    }

    pair<bool, Elem> get(int v, int l, int r, int ask_l, int ask_r) {
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

    void set(int v, int l, int r, int idx, Elem val) {
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

public:
    template<typename t>
    SegTree (const vector<t>& b) {
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

    void update(int ask_l, int ask_r, Promise new_p) {
        update(0, 0, n, ask_l, ask_r, new_p);
    }

    void update(int idx, Promise new_p) {
        update(0, 0, n, idx, idx + 1, new_p);
    }

    Elem get(int ask_l, int ask_r) {
        return get(0, 0, n, ask_l, ask_r).second;
    }

    Elem get(int idx) {
        return get(0, 0, n, idx, idx + 1).second;
    }

    void set(int idx, Elem val) {
        set(0, 0, n, idx, val);
    }
};