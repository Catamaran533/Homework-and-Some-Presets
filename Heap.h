#include <vector>
using namespace std;

template<typename Elem>
class Heap {
private:
    vector<Elem> heap;
    void rise_up(int i) {
        while (0 < i and i < heap.size() and heap[i] < heap[(i - 1) / 2]) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }
    void push_down(int i) {
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
            swap(heap[i], heap[new_i]);
            i = new_i;
        }
    }
public:
    void push(const Elem& val) {
        heap.push_back(val);
        rise_up(heap.size() - 1);
    }
    Elem pop() {
        Elem ans = heap[0];
        swap(heap[0], heap.back());
        heap.pop_back();
        if (heap.size() != 0) {
            push_down(0);
        }
        return ans;
    }
    Elem top() const {
        return heap[0];
    }
    int size() const {
        return heap.size();
    }
    bool empty() const {
        return heap.size() == 0;
    }
};

