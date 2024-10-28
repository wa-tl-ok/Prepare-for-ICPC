//https://codeforces.com/contest/1915/problem/F?locale=ru

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

class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void plus(int const_l, int const_r, int val) {
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
        if (!node || node->lazy == 0) {
            return;
        }

        node->sum += node->lazy * (r - l + 1);

        if (l != r) {
            if (!node->left) {
                node->left = new Node();
            }

            if (!node->right) {
                node->right = new Node();
            }

            node->left->lazy += node->lazy;
            node->right->lazy += node->lazy;
        }

        node->lazy = 0;
    }

    Node* updateRange(Node* node, int l, int r, int const_l, int const_r, int val) {
        if (!node) {
            node = new Node();
        }

        propagate(node, l, r);

        if (const_l > r || const_r < l) {
            return node;
        }

        if (const_l <= l && r <= const_r) {
            node->lazy += val;
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

        int mid = l + (r - l) / 2;

        int leftSum = queryRange(node->left, l, mid, const_l, const_r);
        int rightSum = queryRange(node->right, mid + 1, r, const_l, const_r);

        return leftSum + rightSum;
    }
};

struct Scan_line {
    vector<int> S;
    map<int, int> JUMP;

    map<int, int> id;
    set<int> vis;
    
    vector<pair<int, int>> Get() {
        vector<pair<int, int>> V;
        sort(S.begin(), S.end());
        for (int i = 0; i < S.size(); i++) {
            id[S[i]] = i;
        }
        for (int i = 0; i < S.size(); i++) {
            if (vis.find(S[i]) == vis.end()) {
                vis.insert(S[i]);
                vis.insert(JUMP[S[i]]);
                V.push_back({ id[S[i]], id[JUMP[S[i]]] });
            }
        }
        reverse(V.begin(), V.end());
        return V;
    }
};

vector<int> ANS;

void Solve() {
    ImplicitSegmentTree st(1000000);
    Scan_line sl;

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        sl.S.push_back(a);
        sl.S.push_back(b);
        sl.JUMP[a] = b;
    }

    vector<pair<int, int>> v = sl.Get();

    int ans = 0;
    for (auto p : v) {
        int l = p.first;
        int r = p.second;
        st.plus(r, r, 1);
        ans += st.query(l, r) - 1;
    }

    ANS.push_back(ans);
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

        for (auto ans : ANS) {
            cout << ans << '\n';
        }
    }
    else {
        Solve();
    }

    return 0;
}
