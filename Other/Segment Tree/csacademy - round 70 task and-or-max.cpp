//https://csacademy.com/contest/round-70/task/and-or-max/statement/

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

class Bitwise_SegmentTree {
public:
    Bitwise_SegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void update_and(int l, int r, int val) {
        update_and(1, 0, n - 1, l, r, val);
    }

    void update_or(int l, int r, int val) {
        update_or(1, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

private:
    struct Node {
        int all_or, all_and, lz_or, lz_and, max;
        Node() : all_or(0), all_and((1 << 20) - 1), lz_or(0), lz_and((1 << 20) - 1), max(0) {}

        void apply_and(int val) {
            if (val == (1 << 20) - 1) {
                return;
            }
            all_or &= val; all_and &= val; lz_or &= val; lz_and &= val; max &= val;
        }

        void apply_or(int val) {
            if (val == 0) {
                return;
            }
            all_or |= val; all_and |= val; lz_or |= val; lz_and |= val; max |= val;
        }

        static Node merge(const Node& node_1, const Node& node_2) {
            Node new_node;

            new_node.max = Max(node_1.max, node_2.max);
            new_node.all_or = node_1.all_or | node_2.all_or;
            new_node.all_and = node_1.all_and & node_2.all_and;

            return new_node;
        }

        static int Max(int a, int b) {
            return (a > b) ? a : b;
        }
    };

    vector<Node> tree;
    int n;

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[v].all_and = a[l];
            tree[v].all_or = a[l];
            tree[v].max = a[l];
        }
        else {
            int mid = (l + r) / 2;

            build(2 * v, l, mid, a);
            build(2 * v + 1, mid + 1, r, a);

            tree[v] = Node::merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    void push_down(int v, int l, int r) {
        if (l == r) {
            return;
        }

        tree[2 * v].apply_and(tree[v].lz_and);
        tree[2 * v + 1].apply_and(tree[v].lz_and);

        tree[2 * v].apply_or(tree[v].lz_or);
        tree[2 * v + 1].apply_or(tree[v].lz_or);

        tree[v].lz_and = (1 << 20) - 1;
        tree[v].lz_or = 0;
    }

    void update_or(int v, int l, int r, int const_l, int const_r, int val) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return;
        }

        if (const_l <= l && r <= const_r && ((tree[v].all_and ^ tree[v].all_or) & val) == 0) {
            tree[v].apply_or(val);
            return;
        }

        int mid = (l + r) / 2;

        update_or(2 * v, l, mid, const_l, const_r, val);
        update_or(2 * v + 1, mid + 1, r, const_l, const_r, val);

        tree[v] = Node::merge(tree[2 * v], tree[2 * v + 1]);
    }

    void update_and(int v, int l, int r, int const_l, int const_r, int val) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return;
        }

        if (const_l <= l && r <= const_r && ((tree[v].all_and ^ tree[v].all_or) & ~val) == 0) {
            tree[v].apply_and(val);
            return;
        }

        int mid = (l + r) / 2;

        update_and(2 * v, l, mid, const_l, const_r, val);
        update_and(2 * v + 1, mid + 1, r, const_l, const_r, val);

        tree[v] = Node::merge(tree[2 * v], tree[2 * v + 1]);
    }

    int query(int v, int l, int r, int const_l, int const_r) {
        push_down(v, l, r);

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return tree[v].max;
        }

        int mid = (l + r) / 2;

        int Left = query(2 * v, l, mid, const_l, const_r);
        int Right = query(2 * v + 1, mid + 1, r, const_l, const_r);

        return max(Left, Right);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    Bitwise_SegmentTree BST(a);

    for (int i = 0; i < q; ++i) {
        int type; cin >> type;

        if (type == 1) {
            int ql, qr, x; cin >> ql >> qr >> x;

            --ql;
            --qr;

            BST.update_and(ql, qr, x);
        }
        else if (type == 2) {
            int ql, qr, x; cin >> ql >> qr >> x;

            --ql;
            --qr;

            BST.update_or(ql, qr, x);
        }
        else if (type == 3) {
            int ql, qr; cin >> ql >> qr;

            --ql;
            --qr;

            cout << BST.query(ql, qr) << '\n';
        }
    }

    return 0;
}
