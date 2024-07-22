//https://atcoder.jp/contests/abc331/tasks/abc331_f

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

#define ord(a) (ll) (a);

using namespace std;
using str = string;
using ll = long long;

ll mod = 1e9 + 7;

vector <ll> Step;

int toX(int n) {
    int x = 1;
    while (x * 2 < n) {
        x *= 2;
    }
    x *= 2;
    return x;
}

struct node {
    ll size_l_r;
    ll hash;
    ll reverse_hash;
};

node Empty;

class SegTree {
public:
    SegTree(int n, str s) : size_(n) {
        tree_.resize(2 * n);
        for (int i = n; i < 2 * n; ++i) {
            tree_[i].size_l_r = 1;
            tree_[i].hash = ord(s[i - n]);
            tree_[i].reverse_hash = ord(s[i - n]);
        }
        for (int i = n - 1; i >= 1; --i) {
            tree_[i] = merge(tree_[i * 2], tree_[i * 2 + 1]);
        }
    }

    bool ask(int l, int r) {
        node answer = ask(1, 1, size_, l, r);
        return (answer.hash == answer.reverse_hash);
    }

    node ask(int v, int l, int r, int cl, int cr) {
        if (r < cl || l > cr) {
            return Empty;
        }
        if (l >= cl && r <= cr) {
            return tree_[v];
        }
        int m = (l + r) / 2;
        return merge(ask(v * 2, l, m, cl, cr), ask(v * 2 + 1, m + 1, r, cl, cr));
    }

    void upd(int ind, char val) {
        tree_[ind].hash = ord(val);
        tree_[ind].reverse_hash = ord(val);
        tree_[ind].size_l_r = 1;
        while (ind > 1) {
            ind = ind / 2;
            tree_[ind] = merge(tree_[ind * 2], tree_[ind * 2 + 1]);
        }
        return;
    }

private:
    str s_;
    int size_;
    vector <node> tree_;

    node merge(node a, node b) {
        node new_node;
        new_node.size_l_r = a.size_l_r + b.size_l_r;
        new_node.hash = (a.hash + b.hash * Step[a.size_l_r]) % mod;
        new_node.reverse_hash = (b.reverse_hash + a.reverse_hash * Step[b.size_l_r]) % mod;
        return new_node;
    }
};

void solve() {
    int n, q, p, l, r, x; str s; char c;
    cin >> n >> q >> s;

    int pred_n = n; n = toX(n);
    for (int i = 0; i < n - pred_n; ++i) {
        s.append("a");
    }

    Step.resize(2e6);
    Step[0] = 1;
    for (int i = 1; i < 2e6; ++i) {
        Step[i] = (Step[i - 1] * 31) % mod;
    }

    SegTree DO(n, s);

    for (int i = 0; i < q; ++i) {
        cin >> p;
        if (p == 1) {
            cin >> x >> c;
            DO.upd(x + n - 1, c);
        }
        else {
            cin >> l >> r;
            if (DO.ask(l, r)) {
                cout << "Yes" << "\n";
            }
            else {
                cout << "No" << "\n";
            }
        }
    }
}

int main() {
    solve();
    return 0;
}
