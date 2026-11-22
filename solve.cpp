#include <bits/stdc++.h>
#include "Heap.h"
using namespace std;

void solve() {
    int n;
    cin >> n;
    Heap<int> h;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        h.push(-x);
    }
    while (h.size() >= 2) {
        int mx1 = -h.top();
        h.pop();
        int mx2 = -h.top();
        h.pop();
        if (mx2 == mx1) {
            continue;
        }
        h.push(-(mx1 - mx2));
    }
    if (h.size() == 0) {
        cout << 0 << '\n';
    } else {
        cout << -h.top() << '\n';
    }
}

signed main() {
    solve();
}