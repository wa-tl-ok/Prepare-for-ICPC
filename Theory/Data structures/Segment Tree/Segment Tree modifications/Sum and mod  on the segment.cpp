class JiDriverSegmentTree {
public:
    JiDriverSegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void update_1(int const_l, int const_r, int val) {
        update_1(1, 0, n - 1, const_l, const_r, val);
    }

    void update_2(int qi, int val) {
        update_2(1, 0, n - 1, qi, val);
    }

    int query(int const_l, int const_r) {
        return findSum(1, 0, n - 1, const_l, const_r);
    }

private:
    static const int T = (1 << 20);
    static const int INF = 1e9 + 7;

    struct Node {
        int max;
        int sum;
    };

    vector<Node> tree;
    int n;

    void updateFromChildren(int v) {
        tree[v].sum = tree[2 * v].sum + tree[2 * v + 1].sum;
        tree[v].max = max(tree[2 * v].max, tree[2 * v + 1].max);
    }

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            tree[v].max = a[l];
            tree[v].sum = a[l];
        }
        else {
            int mid = (l + r) / 2;

            build(2 * v, l, mid, a);
            build(2 * v + 1, mid + 1, r, a);

            updateFromChildren(v);
        }
    }

    int findSum(int v, int l, int r, int const_l, int const_r) {
        if (l > r || l > const_r || r < const_l) {
            return 0;
        }

        if (l >= const_l && r <= const_r) {
            return tree[v].sum;
        }

        int mid = (l + r) / 2;

        int leftSum = findSum(2 * v, l, mid, const_l, const_r);
        int RightSum = findSum(2 * v + 1, mid + 1, r, const_l, const_r);

        return leftSum + RightSum;
    }

    void update_2(int v, int l, int r, int qi, int val) {
        if (l == r) {
            tree[v].max = val;
            tree[v].sum = val;

            return;
        }

        int mid = (l + r) / 2;

        if (qi <= mid) {
            update_2(2 * v, l, mid, qi, val);
        }
        else {
            update_2(2 * v + 1, mid + 1, r, qi, val);
        }

        updateFromChildren(v);
    }

    void update_1(int v, int l, int r, int const_l, int const_r, int val) {
        if (l > r || l > const_r || r < const_l || tree[v].max < val) {
            return;
        }

        if (l == r) {
            tree[v].max %= val;
            tree[v].sum = tree[v].max;

            return;
        }

        int mid = (l + r) / 2;

        update_1(2 * v, l, mid, const_l, const_r, val);
        update_1(2 * v + 1, mid + 1, r, const_l, const_r, val);

        updateFromChildren(v);
    }
};
