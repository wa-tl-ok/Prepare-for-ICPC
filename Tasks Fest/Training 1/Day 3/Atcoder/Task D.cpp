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
    SegmentTree() : SegmentTree(0) {}

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

int bs_lr(vector<int>& arr, int target) {
    if (arr[arr.size() - 1] < target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

int bs_rl(vector<int>& arr, int target) {
    if (arr[0] > target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return right;
}

void Solve() {
    vector<string> ANS;

    int n, k; cin >> n >> k;

    vector<int> a(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> rz;
    for (int i = 1; i < n + 2; i++) {
        rz.push_back(a[i] - a[i - 1]);
    }

    /*
    cout << endl;
    cout << "DEBUG ---> " << "difference array : " << endl;
    for (auto p : rz) { cout << p << ' '; } cout << endl;
    cout << endl;
    */

    vector<vector<int>> M(k);
    for (int st = 0; st < k; st++) {
        int now = st;
        while (now < rz.size()) {
            M[st].push_back(rz[now]);
            now += k;
        }
    }

    vector<SegmentTree> ST(k);
    for (int i = 0; i < k; i++) {
        ST[i] = SegmentTree(M[i]);
    }

    vector<vector<int>> IND(k);
    for (int st = 0; st < k; st++) {
        int now = st;
        while (now < rz.size()) {
            IND[st].push_back(now);
            now += k;
        }
    }
    
    int q; cin >> q;
    for (int z = 0; z < q; z++) {
        int l, r; cin >> l >> r;

        l -= 1;
        r -= 0;

        /*
        cout << endl;
        cout << "DEBUG ---> " << "difference array for query : " << endl;;
        for (int i = 0; i < rz.size(); i++) {
            if (i == l) {
                cout << '[' << ' ';
                cout << rz[i] << ' ';
            }
            else if (i == r) {
                cout << rz[i] << ' ';
                cout << ']' << ' ';
            }
            else {
                cout << rz[i] << ' ';
            }
        } cout << endl;
        cout << endl;
        */
        
        string ans = "Yes";

        for (int i = 0; i < k; i++) {
            int L_id = bs_lr(IND[i], l);
            int R_id = bs_rl(IND[i], r);

            int L = IND[i][L_id];
            int R = IND[i][R_id];

            //cout << "DEBUG --->   " << "ost : " << i << " -> L, R = " << L << " " << R << endl;

            int L_q = (L - i) / k;
            int R_q = (R - i) / k;

            int new_l = a[l + 1];
            int new_r = 0 - a[r];

            int was_l = -1;
            int was_r = -1;

            if (l == 0) {
                // pass
            }
            else {
                if (l == L) {
                    was_l = ST[i].query(L_q, L_q);
                    ST[i].change(L_q, L_q, new_l);

                    //cout << "DEBUG ---> " << "Element " << was_l
                    //    << " on position " << l << " was changed by " << new_l << endl;
                }
            }

            if (r == n + 1) {
                // pass
            }
            else {
                if (r == R) {
                    was_r = ST[i].query(R_q, R_q);
                    ST[i].change(R_q, R_q, new_r);

                    //cout << "DEBUG ---> " << "Element " << was_r
                    //    << " on position " << r << " was changed by " << new_r << endl;
                }
            }

            if (ST[i].query(L_q, R_q) != 0) {
                ans = "No";
            }

            if (l == 0) {
                // pass
            }
            else {
                if (l == L) {
                    ST[i].change(L_q, L_q, was_l);

                    //cout << "DEBUG ---> " << "Element " << new_l
                    //    << " on position " << l << " was changed by " << was_l << endl;
                }
            }

            if (r == n + 1) {
                // pass
            }
            else {
                if (r == R) {
                    ST[i].change(R_q, R_q, was_r);

                    //cout << "DEBUG ---> " << "Element " << new_r
                    //    << " on position " << r << " was changed by " << was_r << endl;
                }
            }
        }

        ANS.push_back(ans);
    }

    for (auto e : ANS) {
        cout << e << '\n';
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
