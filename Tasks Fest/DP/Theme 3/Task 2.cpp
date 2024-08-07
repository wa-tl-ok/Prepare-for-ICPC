#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>

using namespace std;

void update(deque<int>& a) {
    if (a.size() == 1) {
        a.push_back(1);
        return;
    }

    a.push_front(0);
    a.push_back(0);

    deque<int> b;
    for (int i = 0; i < (int)a.size() - 1; i++) {
        b.push_back(a[i] + a[i + 1]);
    }

    a = b;
}

void print(const deque<int>& a) {
    for (int i = 0; i < (int)a.size(); i++) {
        cout << a[i] << ' ';
    } cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    deque<int> slice = { 1 };

    for (int i = 1; i <= n; i++) {
        print(slice);
        update(slice);
    }

    return 0;
}
