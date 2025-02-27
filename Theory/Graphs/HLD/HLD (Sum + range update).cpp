class SegmentTree {
public:
    SegmentTree(int size) {
        n = size;
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, 0);
        lazy.assign(p * 2, { 0, false });

        n = p;
    }

    SegmentTree(const vector<int>& a) {
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

class HLD {
public:
    HLD(int size) : n(size), timer(0), Segment_Tree(size) {
        g.resize(n);

        S.resize(n);
        P.resize(n);

        tin.resize(n);
        tout.resize(n);

        head.resize(n);
    }

    void Add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void Decompose(int root = 0) {
        sizes(root);
        head[root] = root;
        hld(root);
    }

    void Update(int v, int value) {
        Segment_Tree.plus(tin[v], tin[v], value);
    }

    void Update(int u, int v, int value) {
        while (!Check(head[u], v)) {
            Segment_Tree.plus(tin[head[u]], tin[u], value);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            Segment_Tree.plus(tin[head[v]], tin[v], value);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        Segment_Tree.plus(tin[u], tin[v], value);
    }

    int Get_sum(int u, int v) {
        int ans = 0;

        while (!Check(head[u], v)) {
            ans += Segment_Tree.query(tin[head[u]], tin[u]);
            u = P[head[u]];
        }

        while (!Check(head[v], u)) {
            ans += Segment_Tree.query(tin[head[v]], tin[v]);
            v = P[head[v]];
        }

        if (!Check(u, v)) {
            swap(u, v);
        }

        return ans + Segment_Tree.query(tin[u], tin[v]);
    }

private:
    int n, timer;
    vector<vector<int>> g;
    vector<int> S, P, tin, tout, head;
    SegmentTree Segment_Tree;

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
