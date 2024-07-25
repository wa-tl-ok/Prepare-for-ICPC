//https://informatics.msk.ru/mod/statements/view.php?id=42416&chapterid=3325#1

#include <iostream> 
#include <iomanip> 
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
#include <climits>

using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<int> ans;

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (a[i] == 0) {
            a[i] = 1;
        }
        else {
            a[i] = 0;
        }
    }

    SegmentTree ST(a);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        string s; cin >> s;
        if (s == "u") {
            int pos, x; cin >> pos >> x;

            if (x == 0) {
                x = 1;
            }
            else {
                x = 0;
            }

            --pos;

            ST.change(pos, pos, x);
        }
        else {
            int l, r; cin >> l >> r;

            --l;
            --r;

            ans.push_back(ST.query(l, r));
        }
    }

    for (auto p : ans) {
        cout << p << ' ';
    }

    return 0;
}
