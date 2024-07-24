class SegmentTreeMax {
public:
    SegmentTreeMax(int size) {
        n = size;
        tree.assign(4 * n, INT_MIN);
        lazy.assign(4 * n, 0);
    }

    SegmentTreeMax(const vector<int>& a) {
        n = (int)a.size();
        tree.assign(4 * n, INT_MIN);
        lazy.assign(4 * n, 0);
        for (int i = 0; i < n; ++i) {
            updateRange(1, 0, n - 1, i, i, a[i], false);
        }
    }

    void plus(int l, int r, int val) {
        updateRange(1, 0, n - 1, l, r, val, true);
    }

    void change(int l, int r, int val) {
        updateRange(1, 0, n - 1, l, r, val, false);
    }

    int queryMax(int l, int r) {
        return queryMaxRange(1, 0, n - 1, l, r);
    }

private:
    vector<int> tree;
    vector<int> lazy;
    int n;

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val, bool isAddition) {
        propagate(node, start, end);
        if (start > end || start > r || end < l) {
            return;
        }
        if (start >= l && end <= r) {
            if (isAddition) {
                tree[node] += val;
                if (start != end) {
                    lazy[2 * node] += val;
                    lazy[2 * node + 1] += val;
                }
            } else {
                tree[node] = val;
                if (start != end) {
                    lazy[2 * node] = val;
                    lazy[2 * node + 1] = val;
                }
            }
            return;
        }
        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val, isAddition);
        updateRange(2 * node + 1, mid + 1, end, l, r, val, isAddition);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int queryMaxRange(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) {
            return INT_MIN;
        }
        propagate(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = queryMaxRange(2 * node, start, mid, l, r);
        int p2 = queryMaxRange(2 * node + 1, mid + 1, end, l, r);
        return max(p1, p2);
    }
};
