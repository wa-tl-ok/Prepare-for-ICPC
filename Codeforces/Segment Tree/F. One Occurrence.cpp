//https://codeforces.com/contest/1000/problem/F

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

class PersistentSegmentTree {
public:
    PersistentSegmentTree(const vector<int>& a) {
        n_ = (int)a.size();
        for (int i = 0; i < (int)a.size(); i++) {
            a_.push_back(a[i]);
        }

        T.resize(n_ + 1);
        T[0] = build(0, n_ - 1);

        vector<int> left(n_);
        unordered_map<int, int> last;

        for (int i = 0; i < n_; ++i) {
            if (!last.count(a_[i])) {
                left[i] = -1;
            }
            else {
                left[i] = last[a_[i]];
            }
            last[a_[i]] = i;
        }

        for (int i = 0; i < n_; ++i) {
            Node* cur = T[i];
            if (left[i] != -1) {
                cur = update(cur, 0, n_ - 1, left[i], 1000000000);
            }
            cur = update(cur, 0, n_ - 1, i, left[i]);
            T[i + 1] = cur;
        }
    }

    int query(int l, int r) {
        pair<int, int> ans = query(T[r + 1], 0, n_ - 1, l, r);

        if (ans.first < l) {
            return a_[ans.second];
        }
        else {
            return 0;
        }
    }

private:
    struct Node {
        pair<int, int> val;
        Node* l;
        Node* r;

        Node() : val(pair<int, int>(1000000000, 0)), l(NULL), r(NULL) {}

        Node(Node* l, Node* r) : l(l), r(r) {
            val = min(l->val, r->val);
        }

        Node(int i, int vi) : l(NULL), r(NULL) {
            this->val = pair<int, int>(vi, i);
        }
    };

    int n_;

    vector<int> a_;
    vector<Node*> T;

    Node* build(int l, int r) {
        if (l == r) {
            return new Node(l, 1000000000);
        }
        else {
            int mid = (l + r) / 2;
            return new Node(build(l, mid), build(mid + 1, r));
        }
    }

    Node* update(Node* t, int l, int r, int pos, int val) {
        if (l == r) {
            return new Node(pos, val);
        }
        else {
            int mid = (l + r) / 2;
            if (pos <= mid) {
                return new Node(update(t->l, l, mid, pos, val), t->r);
            }
            else {
                return new Node(t->l, update(t->r, mid + 1, r, pos, val));
            }
        }
    }

    pair<int, int> query(Node* v, int l, int r, int L, int R) {
        if (L > R) {
            return pair<int, int>(1000000000, 0);
        }
        if (l == L && r == R) {
            return v->val;
        }

        int mid = (l + r) / 2;

        pair<int, int> q1 = query(v->l, l, mid, L, min(mid, R));
        pair<int, int> q2 = query(v->r, mid + 1, r, max(mid + 1, L), R);

        return min(q1, q2);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    PersistentSegmentTree pst(a);

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r;
        cout << pst.query(l - 1, r - 1) << "\n";
    }

    return 0;
}
