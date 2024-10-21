//https://codeforces.com/contest/2009/problem/D

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

void Solve() {
    int n; cin >> n;
    set<int> a;
    set<int> b;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if (y == 0) {
            a.insert(x);
        }
        else {
            b.insert(x);
        }
    }
    for (int x = 0; x <= n; x++) {
        if (a.find(x) != a.end() && b.find(x) != b.end()) {
            ans += n - 2;
        }
        if (a.find(x) != a.end()) {
            if (b.find(x - 1) != b.end() && b.find(x + 1) != b.end()) {
                ++ans;
            }
        }
        if (b.find(x) != b.end()) {
            if (a.find(x - 1) != a.end() && a.find(x + 1) != a.end()) {
                ++ans;
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
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
