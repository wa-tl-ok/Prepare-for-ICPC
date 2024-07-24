class SegmentTreeMin {
public:
    SegmentTreeMin(int size) {
        n = size;
        tree.assign(4 * n, INT_MAX);
        lazy.assign(4 * n, 0);
    }

    SegmentTreeMin(const vector<int>& a) {
        n = (int)a.size();
        tree.assign(4 * n, INT_MAX);
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

    int queryMin(int l, int r) {
        return queryMinRange(1, 0, n - 1, l, r);
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
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    int queryMinRange(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) {
            return INT_MAX;
        }
        propagate(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = queryMinRange(2 * node, start, mid, l, r);
        int p2 = queryMinRange(2 * node + 1, mid + 1, end, l, r);
        return min(p1, p2);
    }
};
