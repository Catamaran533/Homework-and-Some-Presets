#pragma once
#include <vector>

template<typename Elem>
class Heap {
private:
    std::vector<Elem> heap;

    void rise_up(int i);
    void push_down(int i);

public:
    void push(const Elem& val);
    Elem pop();
    Elem top() const;
    int size() const;
    bool empty() const;
};

#include "Heap.cpp"