//https://codeforces.com/contest/1630/problem/A

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
#include <iomanip>

using namespace std;

#define int long long

vector<int> Go1(int n, int k) {
    cout << n - 1 << ' ' << n - 2 << '\n';
    cout << 1 << ' ' << 3 << '\n';
    cout << 0 << ' ' << (3 ^ (n - 1)) << '\n';
    return { n - 1, n - 2, 1, 3, 0, (3 ^ (n - 1)) };
}

vector<int> Go2(int n, int k) {
    if (k != 0) {
        cout << n - 1 << ' ' << k << '\n';
        cout << 0 << ' ' << (k ^ (n - 1)) << '\n';
        return { n - 1, k, 0, (k ^ (n - 1)) };
    }
    else {
        return { };
    }
}

void Solve() {
    int n, k; cin >> n >> k;
    if (n == 4 && k == 3) {
        cout << -1 << '\n';
        return;
    }
    vector<int> a;
    if (k == n - 1) {
        a = Go1(n, k);
    }
    else {
        a = Go2(n, k);
    }
    set<int> s;
    for (auto p : a) {
        s.insert(p);
    }
    for (int i = 0; i < n; i++) {
        if (s.find(i) == s.end()) {
            cout << i << ' ' << (i ^ (n - 1)) << '\n';
            s.insert(i);
            s.insert(i ^ (n - 1));
        }
    }
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
