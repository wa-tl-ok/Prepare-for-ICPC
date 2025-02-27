class TREE {
public:
    TREE(int size) : n(size), timer(0), count_edges(0), 
        SegmentTree_max(size), SegmentTree_min(size), SegmentTree_sum(size) {

        g.resize(n);

        S.resize(n);
        P.resize(n);

        tin.resize(n);
        tout.resize(n);

        head.resize(n);

        vis.resize(n);

        last_ind.resize(n);

        if (n == 1) {
            DECOMPOSE();
        }
    }

    void Add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);

        ++count_edges;

        if (count_edges == n - 1) {
            DECOMPOSE();
        }
    }

    void DECOMPOSE() {
        HLD_Decompose();
    }

    void HLD_Decompose(int root = 0) {
        sizes(root);
        head[root] = root;
        hld(root);
    }

    void plus(int v, int value) {
        /*
            Node v: += value
        */

        SegmentTree_max.plus(tin[v], tin[v], value);
        SegmentTree_min.plus(tin[v], tin[v], value);
        SegmentTree_sum.plus(tin[v], tin[v], value);
    }

    void plus(int u, int v, int value) {
        /*
            All nodes on path u -> v: += value
        */

        while (!Check(head[u], v)) {
            SegmentTree_max.plus(tin[head[u]], tin[u], value);
            SegmentTree_min.plus(tin[head[u]], tin[u], value);
            SegmentTree_sum.plus(tin[head[u]], tin[u], value);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            SegmentTree_max.plus(tin[head[v]], tin[v], value);
            SegmentTree_min.plus(tin[head[v]], tin[v], value);
            SegmentTree_sum.plus(tin[head[v]], tin[v], value);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        SegmentTree_max.plus(tin[u], tin[v], value);
        SegmentTree_min.plus(tin[u], tin[v], value);
        SegmentTree_sum.plus(tin[u], tin[v], value);
    }

    void change(int v, int value) {
        /*
            Node v: = value
        */

        SegmentTree_max.change(tin[v], tin[v], value);
        SegmentTree_min.change(tin[v], tin[v], value);
        SegmentTree_sum.change(tin[v], tin[v], value);
    }

    void change(int u, int v, int value) {
        /*
            All nodes on path u -> v: = value
        */

        while (!Check(head[u], v)) {
            SegmentTree_max.change(tin[head[u]], tin[u], value);
            SegmentTree_min.change(tin[head[u]], tin[u], value);
            SegmentTree_sum.change(tin[head[u]], tin[u], value);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            SegmentTree_max.change(tin[head[v]], tin[v], value);
            SegmentTree_min.change(tin[head[v]], tin[v], value);
            SegmentTree_sum.change(tin[head[v]], tin[v], value);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        SegmentTree_max.change(tin[u], tin[v], value);
        SegmentTree_min.change(tin[u], tin[v], value);
        SegmentTree_sum.change(tin[u], tin[v], value);
    }

    int Get_max(int u, int v) {
        /*
            Get max on path: u -> v
        */

        int ans = std::numeric_limits<int>::min();

        while (!Check(head[u], v)) {
            ans = max(ans, SegmentTree_max.query(tin[head[u]], tin[u]));
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            ans = max(ans, SegmentTree_max.query(tin[head[v]], tin[v]));
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        return max(ans, SegmentTree_max.query(tin[u], tin[v]));
    }

    int Get_min(int u, int v) {
        /*
            Get min on path: u -> v
        */

        int ans = std::numeric_limits<int>::max();

        while (!Check(head[u], v)) {
            ans = min(ans, SegmentTree_min.query(tin[head[u]], tin[u]));
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            ans = min(ans, SegmentTree_min.query(tin[head[v]], tin[v]));
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        return min(ans, SegmentTree_min.query(tin[u], tin[v]));
    }

    int Get_sum(int u, int v) {
        /*
            Get sum on path: u -> v
        */

        int ans = 0;

        while (!Check(head[u], v)) {
            ans += SegmentTree_sum.query(tin[head[u]], tin[u]);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            ans += SegmentTree_sum.query(tin[head[v]], tin[v]);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        return ans + SegmentTree_sum.query(tin[u], tin[v]);
    }

private:
    class SEGMENT_TREE_MAX {
    public:
        SEGMENT_TREE_MAX(int size) {
            n = size;
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 0);
            lazy.assign(p * 2, { 0, false });

            n = p;
        }

        SEGMENT_TREE_MAX(const vector<int>& a) {
            n = (int)a.size();
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 0);
            lazy.assign(p * 2, { 0, false });

            n = p;

            for (int i = 0; i < (int)a.size(); ++i) {
                updateRange(1, 0, n - 1, i, i, a[i], false);
            }
        }

        void plus(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, true);
        }

        void change(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, false);
        }

        int query(int const_l, int const_r) {
            return queryRange(1, 0, n - 1, const_l, const_r);
        }
    private:
        vector<int> tree;
        vector<pair<int, bool>> lazy;
        int n;

        void propagate(int node, int l, int r) {
            if (lazy[node].second) {
                if (lazy[node].first != 0) {
                    tree[node] += lazy[node].first;
                    if (l != r) {
                        lazy[2 * node].first += lazy[node].first;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += lazy[node].first;
                        lazy[2 * node + 1].second = true;
                    }
                }
            }
            else {
                if (lazy[node].first != 0) {
                    tree[node] = lazy[node].first;
                    if (l != r) {
                        lazy[2 * node] = lazy[node];
                        lazy[2 * node + 1] = lazy[node];
                    }
                }
            }
            lazy[node] = { 0, false };
        }

        void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
            propagate(node, l, r);
            if (l > r || l > const_r || r < const_l) {
                return;
            }
            if (l >= const_l && r <= const_r) {
                if (isAddition) {
                    tree[node] += val;
                    if (l != r) {
                        lazy[2 * node].first += val;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += val;
                        lazy[2 * node + 1].second = true;
                    }
                }
                else {
                    tree[node] = val;
                    if (l != r) {
                        lazy[2 * node] = { val, false };
                        lazy[2 * node + 1] = { val, false };
                    }
                }
                return;
            }

            int mid = (l + r) / 2;

            updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
            updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }

        int queryRange(int node, int l, int r, int const_l, int const_r) {
            if (l > r || l > const_r || r < const_l) {
                return 0;
            }

            propagate(node, l, r);

            if (l >= const_l && r <= const_r) {
                return tree[node];
            }

            int mid = (l + r) / 2;

            int p1 = queryRange(2 * node, l, mid, const_l, const_r);
            int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

            return max(p1, p2);
        }
    };

    class SEGMENT_TREE_MIN {
    public:
        SEGMENT_TREE_MIN(int size) {
            n = size;
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 2e9);
            lazy.assign(p * 2, { 0, false });

            n = p;
        }

        SEGMENT_TREE_MIN(const vector<int>& a) {
            n = (int)a.size();
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 2e9);
            lazy.assign(p * 2, { 0, false });

            n = p;

            for (int i = 0; i < (int)a.size(); ++i) {
                updateRange(1, 0, n - 1, i, i, a[i], false);
            }
        }

        void plus(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, true);
        }

        void change(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, false);
        }

        int query(int const_l, int const_r) {
            return queryRange(1, 0, n - 1, const_l, const_r);
        }
    private:
        vector<int> tree;
        vector<pair<int, bool>> lazy;
        int n;

        void propagate(int node, int l, int r) {
            if (lazy[node].second) {
                if (lazy[node].first != 0) {
                    tree[node] += lazy[node].first;
                    if (l != r) {
                        lazy[2 * node].first += lazy[node].first;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += lazy[node].first;
                        lazy[2 * node + 1].second = true;
                    }
                }
            }
            else {
                if (lazy[node].first != 0) {
                    tree[node] = lazy[node].first;
                    if (l != r) {
                        lazy[2 * node] = lazy[node];
                        lazy[2 * node + 1] = lazy[node];
                    }
                }
            }
            lazy[node] = { 0, false };
        }

        void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
            propagate(node, l, r);
            if (l > r || l > const_r || r < const_l) {
                return;
            }
            if (l >= const_l && r <= const_r) {
                if (isAddition) {
                    tree[node] += val;
                    if (l != r) {
                        lazy[2 * node].first += val;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += val;
                        lazy[2 * node + 1].second = true;
                    }
                }
                else {
                    tree[node] = val;
                    if (l != r) {
                        lazy[2 * node] = { val, false };
                        lazy[2 * node + 1] = { val, false };
                    }
                }
                return;
            }

            int mid = (l + r) / 2;

            updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
            updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }

        int queryRange(int node, int l, int r, int const_l, int const_r) {
            if (l > r || l > const_r || r < const_l) {
                return 2e9;
            }

            propagate(node, l, r);

            if (l >= const_l && r <= const_r) {
                return tree[node];
            }

            int mid = (l + r) / 2;

            int p1 = queryRange(2 * node, l, mid, const_l, const_r);
            int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

            return min(p1, p2);
        }
    };

    class SEGMENT_TREE_SUM {
    public:
        SEGMENT_TREE_SUM(int size) {
            n = size;
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 0);
            lazy.assign(p * 2, { 0, false });

            n = p;
        }

        SEGMENT_TREE_SUM(const vector<int>& a) {
            n = (int)a.size();
            int p = 1;
            while (p < n) {
                p *= 2;
            }

            tree.assign(p * 2, 0);
            lazy.assign(p * 2, { 0, false });

            n = p;

            for (int i = 0; i < (int)a.size(); ++i) {
                updateRange(1, 0, n - 1, i, i, a[i], false);
            }
        }

        void plus(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, true);
        }

        void change(int const_l, int const_r, int val) {
            updateRange(1, 0, n - 1, const_l, const_r, val, false);
        }

        int query(int const_l, int const_r) {
            return queryRange(1, 0, n - 1, const_l, const_r);
        }
    private:
        vector<int> tree;
        vector<pair<int, bool>> lazy;
        int n;

        void propagate(int node, int l, int r) {
            if (lazy[node].second) {
                if (lazy[node].first != 0) {
                    tree[node] += lazy[node].first * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node].first += lazy[node].first;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += lazy[node].first;
                        lazy[2 * node + 1].second = true;
                    }
                }
            }
            else {
                if (lazy[node].first != 0) {
                    tree[node] = lazy[node].first * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node] = lazy[node];
                        lazy[2 * node + 1] = lazy[node];
                    }
                }
            }
            lazy[node] = { 0, false };
        }

        void updateRange(int node, int l, int r, int const_l, int const_r, int val, bool isAddition) {
            propagate(node, l, r);
            if (l > r || l > const_r || r < const_l) {
                return;
            }
            if (l >= const_l && r <= const_r) {
                if (isAddition) {
                    tree[node] += val * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node].first += val;
                        lazy[2 * node].second = true;
                        lazy[2 * node + 1].first += val;
                        lazy[2 * node + 1].second = true;
                    }
                }
                else {
                    tree[node] = val * (r - l + 1);
                    if (l != r) {
                        lazy[2 * node] = { val, false };
                        lazy[2 * node + 1] = { val, false };
                    }
                }
                return;
            }

            int mid = (l + r) / 2;

            updateRange(2 * node, l, mid, const_l, const_r, val, isAddition);
            updateRange(2 * node + 1, mid + 1, r, const_l, const_r, val, isAddition);

            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }

        int queryRange(int node, int l, int r, int const_l, int const_r) {
            if (l > r || l > const_r || r < const_l) {
                return 0;
            }

            propagate(node, l, r);

            if (l >= const_l && r <= const_r) {
                return tree[node];
            }

            int mid = (l + r) / 2;

            int p1 = queryRange(2 * node, l, mid, const_l, const_r);
            int p2 = queryRange(2 * node + 1, mid + 1, r, const_l, const_r);

            return p1 + p2;
        }
    };

    int n, timer, count_edges;
    vector<vector<int>> g;
    vector<int> S, P, tin, tout, head, vis, nodes, last_ind;

    SEGMENT_TREE_MAX SegmentTree_max;
    SEGMENT_TREE_MIN SegmentTree_min;
    SEGMENT_TREE_SUM SegmentTree_sum;

    void sizes(int v, int p = -1) {
        S[v] = 1; 
        P[v] = p;

        for (int& u : g[v]) {
            if (u == p) {
                continue;
            }

            sizes(u, v);
            S[v] += S[u];

            if (S[u] > S[g[v][0]]) {
                swap(u, g[v][0]);
            }
        }
    }

    void hld(int v, int p = -1) {
        tin[v] = timer++;

        for (int u : g[v]) {
            if (u == p) {
                continue;
            }

            if (u == g[v][0]) {
                head[u] = head[v];
            }
            else {
                head[u] = u;
            }

            hld(u, v);
        }

        tout[v] = timer;
    }

    bool Check(int a, int b) {
        return tin[a] <= tin[b] && tin[b] < tout[a];
    }
};
