//https://atcoder.jp/contests/abc357/tasks/abc357_f

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
#include <random>

using namespace std;

const int N = 400005;
const int mod = 998244353;

int n, q, a[N], b[N];

struct Segment_tree {
    struct tree {
        int l, r, S;
        int a_sum, b_sum;
        int a_lazy, b_lazy;
    };

    tree p[800010];

    void build(int v, int l, int r) {
        p[v].l = l;
        p[v].r = r;

        if (l == r) {
            return;
        }

        int mid = (p[v].l + p[v].r) / 2;

        build(v * 2, l, mid);
        build(v * 2 + 1, mid + 1, r);
    }

    void solve_a(int v, int d) {
        p[v].a_lazy = (p[v].a_lazy + d) % mod;
        p[v].S = (p[v].S + 1ll * d * p[v].b_sum % mod) % mod;
        p[v].a_sum = (p[v].a_sum + 1ll * d * (p[v].r - p[v].l + 1) % mod) % mod;
    }

    void solve_b(int v, int d) {
        p[v].b_lazy = (p[v].b_lazy + d) % mod;
        p[v].S = (p[v].S + 1ll * d * p[v].a_sum % mod) % mod;
        p[v].b_sum = (p[v].b_sum + 1ll * d * (p[v].r - p[v].l + 1) % mod) % mod;
    }

    void update_a(int v, int l, int r, int d) {
        if (l <= p[v].l && p[v].r <= r) {
            solve_a(v, d);
            return;
        }

        int mid = (p[v].l + p[v].r) / 2;

        if (p[v].a_lazy != 0) {
            solve_a(v * 2, p[v].a_lazy);
            solve_a(v * 2 + 1, p[v].a_lazy);
            p[v].a_lazy = 0;
        }

        if (p[v].b_lazy != 0) {
            solve_b(v * 2, p[v].b_lazy);
            solve_b(v * 2 + 1, p[v].b_lazy);
            p[v].b_lazy = 0;
        }

        if (l <= mid) {
            update_a(v * 2, l, r, d);
        }

        if (r > mid) {
            update_a(v * 2 + 1, l, r, d);
        }

        p[v].S = (p[v * 2].S + p[v * 2 + 1].S) % mod;
        p[v].a_sum = (p[v * 2].a_sum + p[v * 2 + 1].a_sum) % mod;
        p[v].b_sum = (p[v * 2].b_sum + p[v * 2 + 1].b_sum) % mod;
    }

    void update_b(int v, int l, int r, int d) {
        if (l <= p[v].l && p[v].r <= r) {
            solve_b(v, d);
            return;
        }

        int mid = (p[v].l + p[v].r) / 2;

        if (p[v].a_lazy != 0) {
            solve_a(v * 2, p[v].a_lazy);
            solve_a(v * 2 + 1, p[v].a_lazy);
            p[v].a_lazy = 0;
        }

        if (p[v].b_lazy != 0) {
            solve_b(v * 2, p[v].b_lazy);
            solve_b(v * 2 + 1, p[v].b_lazy);
            p[v].b_lazy = 0;
        }

        if (l <= mid) {
            update_b(v * 2, l, r, d);
        }

        if (r > mid) {
            update_b(v * 2 + 1, l, r, d);
        }

        p[v].S = (p[v * 2].S + p[v * 2 + 1].S) % mod;
        p[v].a_sum = (p[v * 2].a_sum + p[v * 2 + 1].a_sum) % mod;
        p[v].b_sum = (p[v * 2].b_sum + p[v * 2 + 1].b_sum) % mod;
    }

    int query(int v, int l, int r) {
        if (l <= p[v].l && p[v].r <= r) {
            return p[v].S;
        }

        int mid = (p[v].l + p[v].r) / 2;
        int sum = 0;

        if (p[v].a_lazy != 0) {
            solve_a(v * 2, p[v].a_lazy);
            solve_a(v * 2 + 1, p[v].a_lazy);
            p[v].a_lazy = 0;
        }

        if (p[v].b_lazy != 0) {
            solve_b(v * 2, p[v].b_lazy);
            solve_b(v * 2 + 1, p[v].b_lazy);
            p[v].b_lazy = 0;
        }

        if (l <= mid) {
            sum = (sum + query(v * 2, l, r)) % mod;
        }

        if (r > mid) {
            sum = (sum + query(v * 2 + 1, l, r)) % mod;
        }

        return sum;
    }
};

Segment_tree T;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    T.build(1, 1, n);

    for (int i = 1; i <= n; ++i) {
        T.update_a(1, i, i, a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        T.update_b(1, i, i, b[i]);
    }

    for (int i = 0; i < q; i++) {
        int Type; cin >> Type;
        if (Type == 1) {
            int l, r, x;
            cin >> l >> r >> x;

            T.update_a(1, l, r, x);
        }
        else if (Type == 2) {
            int l, r, x;
            cin >> l >> r >> x;

            T.update_b(1, l, r, x);
        }
        else {
            int l, r;
            cin >> l >> r;

            cout << T.query(1, l, r) << "\n";
        }
    }

    return 0;
}
