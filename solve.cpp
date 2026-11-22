#include <iostream>
#include "Stack.h"
using namespace std;

void solve() {
    Stack a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push(x);
    }
    Stack b;
    while (a.size() != 0) {
        int curr = a.top();
        a.pop();
        while (b.size() > 0 and b.top() < curr) {
            a.push(b.top());
            b.pop();
        }
        b.push(curr);
    }
    b.print();
}

signed main() {
    solve();
}