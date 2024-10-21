//https://codeforces.com/contest/1579/problem/E2

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

    void plus(int pos, int val) {
        root = updatePoint(root, 0, n - 1, pos, val);
    }

    int query(int const_l, int const_r) {
        return queryRange(root, 0, n - 1, const_l, const_r);
    }

private:
    struct Node {
        int sum;
        Node* left;
        Node* right;

        Node() : sum(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->sum += val;
            return node;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            node->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            node->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

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

int inverse(vector <int>& a) {
    int inv_count = 0;
    if (a.size() > 1) {
        int mid = a.size() / 2;
        vector<int> left(a.begin(), a.begin() + mid);
        vector<int> right(a.begin() + mid, a.end());
        inv_count += inverse(left);
        inv_count += inverse(right);
        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                a[k] = left[i];
                i++;
            }
            else {
                a[k] = right[j];
                j++;
                inv_count += left.size() - i;
            }
            k++;
        }
        while (i < left.size()) {
            a[k] = left[i];
            i++;
            k++;
        }
        while (j < right.size()) {
            a[k] = right[j];
            j++;
            k++;
        }
    }
    return inv_count;
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += 1'000'000'000;
    }
    ImplicitSegmentTree st(2'000'000'005);
    deque<int> p = { a[0] };
    st.plus(a[0], 1);
    for (int i = 1; i < n; i++) {
        int lower = st.query(0, a[i] - 1);
        int upper = st.query(a[i] + 1, 2'000'000'003);
        if (lower > upper) {
            p.push_back(a[i]);
        }
        else {
            p.push_front(a[i]);
        }
        st.plus(a[i], 1);
    }
    vector<int> b;
    for (auto t : p) {
        b.push_back(t);
    }
    cout << inverse(b) << '\n';
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
