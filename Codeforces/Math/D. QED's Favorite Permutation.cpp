//https://codeforces.com/contest/2030/problem/D

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

class SegmentTree {
public:
    SegmentTree(int size) {
        n = size;
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, 0);
        lazy.assign(p * 2, { 0, false });

        n = p;
    }

    SegmentTree(const vector<int>& a) {
        n = (int)a.size();
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, 0);
        lazy.assign(p * 2, { 0, false });

        n = p;

        for (int i = 0; i < (int)a.size(); ++i) {
            updateRange(1, 0, n - 1, i, i, a[i], false);
        }
    }

    void plus(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, true);
    }

    void change(int const_l, int const_r, int val) {
        updateRange(1, 0, n - 1, const_l, const_r, val, false);
    }

    int query(int const_l, int const_r) {
        return queryRange(1, 0, n - 1, const_l, const_r);
    }
private:
    vector<int> tree;
    vector<pair<int, bool>> lazy;
    int n;

    void propagate(int node, int l, int r) {
        if (lazy[node].second) {
            if (lazy[node].first != 0) {
                tree[node] += lazy[node].first * (r - l + 1);
                if (l != r) {
                    lazy[2 * node].first += lazy[node].first;
                    lazy[2 * node].second = true;
                    lazy[2 * node + 1].first += lazy[node].first;
                    lazy[2 * node + 1].second = true;
                }
            }
        }
        else {
            if (lazy[node].first != 0) {
                tree[node] = lazy[node].first * (r - l + 1);
                if (l != r) {
                    lazy[2 * node] = lazy[node];
                    lazy[2 * node + 1] = lazy[node];
                }
            }
        }
        lazy[node] = { 0, false };
    }

    void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
        propagate(node, l, r);
        if (l > r || l > const_r || r < const_l) {
            return;
        }
        if (l >= const_l && r <= const_r) {
            if (isAddition) {
                tree[node] += val * (r - l + 1);
                if (l != r) {
                    lazy[2 * node].first += val;
                    lazy[2 * node].second = true;
                    lazy[2 * node + 1].first += val;
                    lazy[2 * node + 1].second = true;
                }
            }
            else {
                tree[node] = val * (r - l + 1);
                if (l != r) {
                    lazy[2 * node] = { val, false };
                    lazy[2 * node + 1] = { val, false };
                }
            }
            return;
        }

        int mid = (l + r) / 2;

        updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
        updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int queryRange(int node, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return 0;
        }

        propagate(node, l, r);

        if (l >= const_l && r <= const_r) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        int p1 = queryRange(2 * node, l, mid, const_l, const_r);
        int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

        return p1 + p2;
    }
};

void Solve() {
    int n; cin >> n;
    int q; cin >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        --a[i];
    }
    string s; cin >> s;
    SegmentTree st(n);
    set<int> g;
    for (int i = 0; i < n; i++) {
        st.plus(a[i], a[i], 1);
        if (st.query(0, i) == i + 1) {
            if (i > 0 && i < n - 1) {
                g.insert(i);
            }
        }
    }

    set<int> bad;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'L' && s[i + 1] == 'R') {
            if (g.find(i) == g.end()) {
                bad.insert(i);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int p; cin >> p;
        --p;
        if (s[p] == 'L') {
            if (s[p - 1] == 'R' && s[p + 1] == 'R') {
                bad.erase(p);
            }
            else if (s[p - 1] == 'L' && s[p + 1] == 'L') {
                if (g.find(p - 1) == g.end()) {
                    bad.insert(p - 1);
                }
            }
            else if (s[p - 1] == 'L' && s[p + 1] == 'R') {
                bad.erase(p);
                if (g.find(p - 1) == g.end()) {
                    bad.insert(p - 1);
                }
            }
            else if (s[p - 1] == 'R' && s[p + 1] == 'L') {
                // pass
            }
        }
        else {
            if (s[p - 1] == 'R' && s[p + 1] == 'R') {
                if (g.find(p) == g.end()) {
                    bad.insert(p);
                }
            }
            else if (s[p - 1] == 'L' && s[p + 1] == 'L') {
                bad.erase(p - 1);
            }
            else if (s[p - 1] == 'L' && s[p + 1] == 'R') {
                bad.erase(p - 1);
                if (g.find(p) == g.end()) {
                    bad.insert(p);
                }
            }
            else if (s[p - 1] == 'R' && s[p + 1] == 'L') {
                // pass
            }
        }

        if (bad.size() == 0) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }

        if (s[p] == 'L') {
            s[p] = 'R';
        }
        else {
            s[p] = 'L';
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
