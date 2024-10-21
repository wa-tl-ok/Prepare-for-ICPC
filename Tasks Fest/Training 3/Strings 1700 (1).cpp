//https://codeforces.com/contest/670/problem/E

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

class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void change(int const_l, int const_r, int val) {
        root = updateRange(root, 0, n - 1, const_l, const_r, val);
    }

    int query(int const_l, int const_r) {
        return queryRange(root, 0, n - 1, const_l, const_r);
    }

private:
    struct Node {
        int sum;
        int lazy;

        Node* left;
        Node* right;

        Node() : sum(0), lazy(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    void propagate(Node* node, int l, int r) {
        if (!node || node->lazy == -1) {
            return;
        }

        node->sum = node->lazy * (r - l + 1);

        if (l != r) {
            if (!node->left) {
                node->left = new Node();
            }

            if (!node->right) {
                node->right = new Node();
            }

            node->left->lazy = node->lazy;
            node->right->lazy = node->lazy;
        }

        node->lazy = -1;
    }

    Node* updateRange(Node* node, int l, int r, int const_l, int const_r, int val) {
        if (!node) {
            node = new Node();
        }

        if (val == 0) {
            if (node->sum == 0) {
                return node;
            }
        }

        propagate(node, l, r);

        if (const_l > r || const_r < l) {
            return node;
        }

        if (const_l <= l && r <= const_r) {
            node->lazy = val;
            propagate(node, l, r);

            return node;
        }

        int mid = l + (r - l) / 2;

        node->left = updateRange(node->left, l, mid, const_l, const_r, val);
        node->right = updateRange(node->right, mid + 1, r, const_l, const_r, val);

        node->sum = 0;
        if (node->left) {
            node->sum += node->left->sum;
        }
        if (node->right) {
            node->sum += node->right->sum;
        }

        return node;
    }

    int queryRange(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return 0;
        }

        propagate(node, l, r);

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return node->sum;
        }

        if (node->sum == 0) {
            return 0;
        }

        int mid = l + (r - l) / 2;

        int leftSum = queryRange(node->left, l, mid, const_l, const_r);
        int rightSum = queryRange(node->right, mid + 1, r, const_l, const_r);

        return leftSum + rightSum;
    }
};

int next_right(int p, int n, ImplicitSegmentTree& st) {
    int l = p;
    int r = n + 1;
    while (l + 1 != r) {
        int m = (l + r) / 2;
        if (st.query(p + 1, m) >= 1) {
            r = m;
        }
        else {
            l = m;
        }
    }
    return r;
}

int next_left(int p, int n, ImplicitSegmentTree& st) {
    int l = -1;
    int r = p;
    while (l + 1 != r) {
        int m = (l + r) / 2;
        if (st.query(m, p - 1) >= 1) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return l;
}

void Solve() {
    int n, m, p;
    cin >> n >> m >> p;
    --p;
    string S; cin >> S;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (S[i] == '(') {
            a[i] = 1;
        }
        else {
            a[i] = -1;
        }
    }
    vector<int> bal(n);
    vector<int> go(n);
    for (int i = 0; i < n; i++) {
        bal[i] = -1;
        go[i] = -1;
    }
    int b = 0;
    for (int i = 0; i < n; i++) {
        b += a[i];
        if (S[i] == '(') {
            if (bal[b - 1] != -1) {
                go[i] = bal[b - 1];
                go[bal[b - 1]] = i;
                bal[b - 1] = -1;
            }
            else {
                bal[b - 1] = i;
            }
        }
        else {
            if (bal[b] != -1) {
                go[i] = bal[b];
                go[bal[b]] = i;
                bal[b] = -1;
            }
            else {
                bal[b] = i;
            }
        }
    }
    ImplicitSegmentTree st(n);
    for (int i = 0; i < n; i++) {
        st.change(i, i, 1);
    }
    string Instruction; cin >> Instruction;
    for (int i = 0; i < m; i++) {
        if (Instruction[i] == 'L') {
            p = next_left(p, n, st);
        }
        else if (Instruction[i] == 'R') {
            p = next_right(p, n, st);
        }
        else {
            int l = p;
            int r = go[p];
            if (l > r) {
                swap(l, r);
            }
            st.change(l, r, 0);
            if (st.query(l, n) != 0) {
                p = next_right(l, n, st);
            }
            else {
                p = next_left(l, n, st);
            }
        }
    }
    for (int i = 0; i < a.size(); i++) {
        if (st.query(i, i) == 1) {
            if (a[i] == 1) {
                cout << '(';
            }
            else {
                cout << ')';
            }
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
