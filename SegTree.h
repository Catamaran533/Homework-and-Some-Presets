#pragma once
#include <vector>
#include <utility>
#include <type_traits>

class DefaultPromise {};

template<typename Elem, typename Promise = DefaultPromise>
class SegTree {
private:
    int n;
    std::vector<Elem> a;
    std::vector<Elem> tree;
    std::vector<Promise> p;
    std::vector<bool> have_p;

    static constexpr bool available_promise = not std::is_same_v<Promise, DefaultPromise>;

    void build(int v, int l, int r);
    void update_promise(int v, Promise new_p);
    void do_promise(int v);
    void push(int v, int l, int r);
    void update(int v, int l, int r, int ask_l, int ask_r, Promise new_p);
    std::pair<bool, Elem> merge(const std::pair<bool, Elem>& pa, const std::pair<bool, Elem>& pb) const;
    std::pair<bool, Elem> get(int v, int l, int r, int ask_l, int ask_r);
    void set(int v, int l, int r, int idx, Elem val);

public:
    template<typename t>
    SegTree(const std::vector<t>& b);

    void update(int ask_l, int ask_r, Promise new_p);
    void update(int idx, Promise new_p);
    Elem get(int ask_l, int ask_r);
    Elem get(int idx);
    void set(int idx, Elem val);
};

#include "SegTree.cpp"