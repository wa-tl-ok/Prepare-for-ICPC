//https://codeforces.com/contest/2005/problem/B2

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

pair<int, int> Find(vector<int>& a, int x) {
    int l = -1;
    int r = a.size();
    while (l + 1 != r) {
        int m = (l + r) / 2;
        if (a[m] < x) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return { a[l], a[r] };
}

void Solve() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        if (x < b[0]) {
            cout << b[0] - 1 << '\n';
        }
        else if (x > b[b.size() - 1]) {
            cout << n - b[b.size() - 1] << '\n';
        }
        else {
            pair<int, int> p = Find(b, x);
            int l = p.first;
            int r = p.second;
            cout << (r - l) / 2 << '\n';
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
