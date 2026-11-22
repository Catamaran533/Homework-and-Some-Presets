#pragma once
#include "Heap.h"
#include <utility>

template<typename Elem>
void Heap<Elem>::rise_up(int i) {
    while (0 < i and i < heap.size() and heap[i] < heap[(i - 1) / 2]) {
        std::swap(heap[(i - 1) / 2], heap[i]);
        i = (i - 1) / 2;
    }
}

template<typename Elem>
void Heap<Elem>::push_down(int i) {
    while (2 * i + 1 < heap.size()) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int new_i = l;
        if (r < heap.size() and heap[r] < heap[l]) {
            new_i = r;
        }
        if (not (heap[new_i] < heap[i])) {
            break;
        }
        std::swap(heap[i], heap[new_i]);
        i = new_i;
    }
}

template<typename Elem>
void Heap<Elem>::push(const Elem& val) {
    heap.push_back(val);
    rise_up(heap.size() - 1);
}

template<typename Elem>
Elem Heap<Elem>::pop() {
    if (heap.empty()) {
        throw "Error in method pop: Impossible to call it if heap is empty";
    }
    Elem ans = heap[0];
    std::swap(heap[0], heap.back());
    heap.pop_back();
    if (not heap.empty()) {
        push_down(0);
    }
    return ans;
}

template<typename Elem>
Elem Heap<Elem>::top() const {
    if (heap.empty()) {
        throw "Error in method top: Impossible to call it if heap is empty";
    }
    return heap[0];
}

template<typename Elem>
int Heap<Elem>::size() const {
    return heap.size();
}

template<typename Elem>
bool Heap<Elem>::empty() const {
    return heap.empty();
}