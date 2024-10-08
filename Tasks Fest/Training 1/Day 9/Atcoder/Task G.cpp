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

class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) { x = 0; ans = 0; }

    void Plus(int pos, int val_1, int val_2) {
        root = Update(root, 0, n - 1, pos, val_1, val_2);
    }

    int Check(int const_l, int const_r) {
        return Check(root, 0, n - 1, const_l, const_r);
    }

    int Solve(int xq) {
        Go(xq);
        return ans;
    }
private:
    struct Node {
        int sum;
        int sumq;

        Node* left;
        Node* right;

        Node() : sum(0), sumq(0),
            left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    int x;
    int ans;

    Node* Update(Node* node, int l, int r, int pos, int val_1, int val_2) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->sum += val_1;
            node->sumq += val_2;
            return node;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            node->left = Update(node->left, l, mid, pos, val_1, val_2);
        }
        else {
            node->right = Update(node->right, mid + 1, r, pos, val_1, val_2);
        }

        node->sum = 0;
        if (node->left) {
            node->sum = node->left->sum;
        }
        if (node->right) {
            node->sum += node->right->sum;
        }

        node->sumq = 0;
        if (node->left) {
            node->sumq = node->left->sumq;
        }
        if (node->right) {
            node->sumq += node->right->sumq;
        }

        return node;
    }

    int Check(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return 0;
        }

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return node->sum;
        }

        int mid = l + (r - l) / 2;

        int leftSum = Check(node->left, l, mid, const_l, const_r);
        int rightSum = Check(node->right, mid + 1, r, const_l, const_r);

        return leftSum + rightSum;
    }

    int Go(int xq) {
        x = xq; ans = 0;
        Solve(root, 0, n - 1, 0, n - 1);
        return ans;
    }

    void Solve(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            ans += 0;
            return;
        }

        if (x == 0) {
            ans += 0;
            return;
        }

        if (l == r) {
            if (node->sum <= x) {
                ans += node->sumq; x -= node->sum;
                return;
            }
            else {
                ans += node->sumq / node->sum * x; x = 0;
                return;
            }
        }

        if (node->sum <= x) {
            x -= node->sum;
            ans += node->sumq;
            return;
        }
        else {
            int mid = l + (r - l) / 2;

            Solve(node->right, mid + 1, r, const_l, const_r);
            Solve(node->left, l, mid, const_l, const_r);

            return;
        }
    }
} IST(1e9 + 5);

void Solve() {
    vector<int> ANS;

    int n; cin >> n;

    map<int, pair<int, int>> Cards;
    for (int id = 1; id <= n; id++) {
        int a; cin >> a;
        int b; cin >> b;

        Cards[id] = { a, b };
    }

    for (int id= 1; id <= n; id++) {
        int a = Cards[id].first;
        int b = Cards[id].second;

        IST.Plus(a, b, a * b);
    }

    int q; cin >> q;

    for (int i = 0; i < q; i++) {
        int t; cin >> t;

        if (t == 1) {
            int id; cin >> id;
            int new_a; cin >> new_a;

            IST.Plus(new_a, Cards[id].second, Cards[id].second * new_a);
            IST.Plus(Cards[id].first, -Cards[id].second, -Cards[id].second * Cards[id].first);

            Cards[id].first = new_a;
        }
        else if (t == 2) {
            int id; cin >> id;
            int new_b; cin >> new_b;

            IST.Plus(Cards[id].first, new_b - Cards[id].second, (new_b - Cards[id].second) * Cards[id].first);

            Cards[id].second = new_b;
        }
        else {
            int x; cin >> x;

            if (IST.Check(0, 1e9 + 3) < x) {
                ANS.push_back(-1);
            }
            else {
                ANS.push_back(IST.Solve(x));
            }
        }
    }

    for (auto p : ANS) {
        cout << p << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
    if (multitest) {
        int test_cases;
        cin >> test_cases;
        for (int i = 0; i < test_cases; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
