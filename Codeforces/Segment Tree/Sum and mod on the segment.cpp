//https://codeforces.com/group/1rv4rhCsHp/contest/327313/problem/A

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

class JiDriverSegmentTree {
public:
    JiDriverSegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void update_1(int const_l, int const_r, int val) {
        update_1(1, 0, n - 1, const_l, const_r, val);
    }

    void update_2(int qi, int val) {
        update_2(1, 0, n - 1, qi, val);
    }

    long long query(int const_l, int const_r) {
        return findSum(1, 0, n - 1, const_l, const_r);
    }

private:
    struct Node {
        int max;
        long long sum;
    };

    vector<Node> tree;
    int n;

    void updateFromChildren(int v) {
        tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
        tree[v].max = max(tree[2 * v].max, tree[2 * v + 1].max);
    }

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[v].max = a[l];
            tree[v].sum = a[l];
        }
        else {
            int mid = (l + r) / 2;

            build(2 * v, l, mid, a);
            build(2 * v + 1, mid + 1, r, a);

            updateFromChildren(v);
        }
    }

    long long findSum(int v, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return 0;
        }

        if (l >= const_l && r <= const_r) {
            return tree[v].sum;
        }

        int mid = (l + r) / 2;

        long long leftSum = findSum(2 * v, l, mid, const_l, const_r);
        long long RightSum = findSum(2 * v + 1, mid + 1, r, const_l, const_r);

        return leftSum + RightSum;
    }

    void update_2(int v, int l, int r, int qi, int val) {
        if (l == r) {
            tree[v].max = val;
            tree[v].sum = val;

            return;
        }

        int mid = (l + r) / 2;

        if (qi <= mid) {
            update_2(2 * v, l, mid, qi, val);
        }
        else {
            update_2(2 * v + 1, mid + 1, r, qi, val);
        }

        updateFromChildren(v);
    }

    void update_1(int v, int l, int r, int const_l, int const_r, int val) {
        if (l > r || l > const_r || r < const_l || tree[v].max < val) {
            return;
        }

        if (l == r) {
            tree[v].max %= val;
            tree[v].sum = tree[v].max;

            return;
        }

        int mid = (l + r) / 2;

        update_1(2 * v, l, mid, const_l, const_r, val);
        update_1(2 * v + 1, mid + 1, r, const_l, const_r, val);

        updateFromChildren(v);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q; cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    JiDriverSegmentTree ST(a);
    for (int i = 0; i < q; i++) {
        int type; cin >> type;

        if (type == 1) {
            int ql, qr; cin >> ql >> qr;

            --ql;
            --qr;

            cout << ST.query(ql, qr) << '\n';
        }
        else if (type == 2) {
            int ql, qr, x; cin >> ql >> qr >> x;

            --ql;
            --qr;

            ST.update_1(ql, qr, x);
        }
        else if (type == 3) {
            int qi, y; cin >> qi >> y;

            --qi;

            ST.update_2(qi, y);
        }
    }
    return 0;
}
