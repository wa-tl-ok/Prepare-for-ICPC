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

#define int long long

bool Check(vector<int> toys, vector<int> boxes) {
    sort(toys.begin(), toys.end());
    sort(boxes.begin(), boxes.end());
    for (int i = 0; i < toys.size(); i++) {
        if (toys[i] > boxes[i]) {
            return false;
        }
    }
    return true;
}

void Solve() {
    int n; cin >> n;
    vector<int> toys(n);
    for (int i = 0; i < n; i++) {
        cin >> toys[i];
    }
    vector<int> boxes(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> boxes[i];
    }
    int l = 0;
    int r = 1e18;
    while (l + 1 != r) {
        int m = (l + r) / 2;
        boxes.push_back(m);
        bool F = Check(toys, boxes);
        boxes.pop_back();
        if (F == true) {
            r = m;
        }
        else {
            l = m;
        }
    }
    if (r == 1e18) {
        cout << -1;
    }
    else {
        cout << r;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
