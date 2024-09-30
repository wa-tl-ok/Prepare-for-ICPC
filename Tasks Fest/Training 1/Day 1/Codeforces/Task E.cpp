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

class SegmentTree {
public:
    SegmentTree(int size) {
        n = size;
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree_min.assign(p * 2, 0);
        tree_max.assign(p * 2, 0);
        lazy.assign(p * 2, 0);

        n = p;
    }

    void plus(int left, int right, int value) {
        updateRange(1, 0, n - 1, left, right, value);
    }

    int query_min(int left, int right) {
        return queryRangeMin(1, 0, n - 1, left, right);
    }

    int query_max(int left, int right) {
        return queryRangeMax(1, 0, n - 1, left, right);
    }

private:
    vector<int> tree_min;
    vector<int> tree_max;
    vector<int> lazy;
    int n;

    void propagate(int node, int l, int r) {
        if (lazy[node] != 0) {
            tree_min[node] += lazy[node];
            tree_max[node] += lazy[node];

            if (l != r) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }

            lazy[node] = 0;
        }
    }

    void updateRange(int node, int l, int r, int const_l, int const_r, int value) {
        propagate(node, l, r);

        if (l > r || l > const_r || r < const_l) {
            return;
        }

        if (l >= const_l && r <= const_r) {
            tree_min[node] += value;
            tree_max[node] += value;

            if (l != r) {
                lazy[2 * node] += value;
                lazy[2 * node + 1] += value;
            }

            return;
        }

        int mid = (l + r) / 2;
        updateRange(2 * node, l, mid, const_l, const_r, value);
        updateRange(2 * node + 1, mid + 1, r, const_l, const_r, value);

        tree_min[node] = min(tree_min[2 * node], tree_min[2 * node + 1]);
        tree_max[node] = max(tree_max[2 * node], tree_max[2 * node + 1]);
    }

    int queryRangeMin(int node, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return 2e9;
        }

        propagate(node, l, r);

        if (l >= const_l && r <= const_r) {
            return tree_min[node];
        }

        int mid = (l + r) / 2;
        int leftMin = queryRangeMin(2 * node, l, mid, const_l, const_r);
        int rightMin = queryRangeMin(2 * node + 1, mid + 1, r, const_l, const_r);

        return min(leftMin, rightMin);
    }

    int queryRangeMax(int node, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return -2e9;
        }

        propagate(node, l, r);

        if (l >= const_l && r <= const_r) {
            return tree_max[node];
        }

        int mid = (l + r) / 2;
        int leftMax = queryRangeMax(2 * node, l, mid, const_l, const_r);
        int rightMax = queryRangeMax(2 * node + 1, mid + 1, r, const_l, const_r);

        return max(leftMax, rightMax);
    }
};

void Solve() {
    int n; cin >> n;
    string s; cin >> s;

    int N = 1e6 + 3;

    SegmentTree st(N + 2);

    string S = "";
    for (int i = 0; i < N + 2; i++) {
        S += ".";
    }

    int B = 0;

    int now = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'L') {
            --now;

            if (now < 0) {
                now = 0;
            }
        }
        else if (s[i] == 'R') {
            ++now;
        }
        else {
            if (s[i] == '(') {
                if (S[now] == '(') {
                    // pass
                }
                else if (S[now] == ')') {
                    st.plus(now, N, 2);
                    B += 2;
                }
                else {
                    st.plus(now, N, 1);
                    B += 1;
                }
            }
            else if (s[i] == ')') {
                if (S[now] == '(') {
                    st.plus(now, N, -2);
                    B -= 2;
                }
                else if (S[now] == ')') {
                    // pass
                }
                else {
                    st.plus(now, N, -1);
                    B -= 1;
                }
            }
            else {
                if (S[now] == '(') {
                    st.plus(now, N, -1);
                    B -= 1;
                }
                else if (S[now] == ')') {
                    st.plus(now, N, 1);
                    B += 1;
                }
                else {
                    // pass
                }
            }

            S[now] = s[i];
        }

        if (st.query_min(0, N) < 0 || B != 0) { 
            cout << -1 << ' '; 
        }
        else { 
            cout << st.query_max(0, N) << ' ';
        }
    }
}

int main() {
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
