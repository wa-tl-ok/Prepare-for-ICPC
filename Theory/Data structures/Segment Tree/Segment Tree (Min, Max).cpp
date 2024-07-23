class SegmentTree_min_max {
public:
    SegmentTree_min_max(int size) {
        n = size;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        minVal.assign(4 * n, 0);
        maxVal.assign(4 * n, 0);
    }

    SegmentTree_min_max(const vector<int>& a) {
        n = (int)a.size();

        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        minVal.assign(4 * n, 0);
        maxVal.assign(4 * n, 0);

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

    int queryMax(int l, int r) {
        return queryMaxRange(1, 0, n - 1, l, r);
    }

private:
    vector<int> tree;
    vector<int> lazy;
    vector<int> minVal;
    vector<int> maxVal;
    int n;

    int queryMinRange(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) {
            return INT_MAX;
        }

        propagate(node, start, end);

        if (start >= l && end <= r) {
            return minVal[node];
        }
        int mid = (start + end) / 2;

        int p1 = queryMinRange(2 * node, start, mid, l, r);
        int p2 = queryMinRange(2 * node + 1, mid + 1, end, l, r);

        return min(p1, p2);
    }

    int queryMaxRange(int node, int start, int end, int l, int r) {
        if (start > end || start > r || end < l) {
            return INT_MIN;
        }

        propagate(node, start, end);

        if (start >= l && end <= r) {
            return maxVal[node];
        }
        int mid = (start + end) / 2;

        int p1 = queryMaxRange(2 * node, start, mid, l, r);
        int p2 = queryMaxRange(2 * node + 1, mid + 1, end, l, r);

        return max(p1, p2);
    }

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (end - start + 1);
            minVal[node] += lazy[node];
            maxVal[node] += lazy[node];
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
                tree[node] += val * (end - start + 1);
                minVal[node] += val;
                maxVal[node] += val;
                if (start != end) {
                    lazy[2 * node] += val;
                    lazy[2 * node + 1] += val;
                }
            }
            else {
                tree[node] = val * (end - start + 1);
                minVal[node] = val;
                maxVal[node] = val;
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

        tree[node] = tree[2 * node] + tree[2 * node + 1];

        minVal[node] = min(minVal[2 * node], minVal[2 * node + 1]);
        maxVal[node] = max(maxVal[2 * node], maxVal[2 * node + 1]);
    }
};

void ToUseSegTree_min_max() {
    SegmentTree_min_max segTree({ 0, 0, 0, 0, 0, 0 });

    segTree.plus(0, 5, 1);
    segTree.plus(0, 3, 2);
    segTree.change(1, 4, 5);

    int answer1 = segTree.queryMin(0, 5);
    int answer2 = segTree.queryMax(0, 5);
}
