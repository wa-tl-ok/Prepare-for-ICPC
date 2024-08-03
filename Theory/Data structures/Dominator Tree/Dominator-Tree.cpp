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

void print(vector<int>& a) {
    for (auto q : a) {
        cout << q << ' ';
    }
    cout << "\n";
}

class SegmentTree {
public:
    SegmentTree(int size) {
        n = size;
        int p = 1;
        while (p < n) {
            p *= 2;
        }

        tree.assign(p * 2, 2e9);
        lazy.assign(p * 2, { 0, false });

        n = p;
    }

    SegmentTree(const vector<int>& a) {
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
        Segment_Tree.change(tin[v], tin[v], value);
    }

    int Get_min(int u, int v) {
        int ans = 2e9;
        while (Check(head[u], v) == false) {
            ans = min(ans, Segment_Tree.query(tin[head[u]], tin[u]));
            u = P[head[u]];
        }
        while (Check(head[v], u) == false) {
            ans = min(ans, Segment_Tree.query(tin[head[v]], tin[v]));
            v = P[head[v]];
        }
        if (Check(u, v) == false) {
            swap(u, v);
        }
        return min(ans, Segment_Tree.query(tin[u], tin[v]));
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

struct DSU {
    vector<int> head;
    vector<int> rang;
    vector<int> DSU_Sdom;
    vector<int> DSU_tin;

    DSU(int n, vector<int>& Sdom, vector<int>& tin) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        DSU_Sdom.resize(n);
        for (int i = 0; i < n; i++) {
            DSU_Sdom[i] = Sdom[i];
        }

        DSU_tin.resize(n);
        for (int i = 0; i < n; i++) {
            DSU_tin[i] = tin[i];
        }
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return Find(head[x]);
    }

    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);

        if (x == y) {
            return false;
        }

        if (rang[x] < rang[y]) {
            rang[y] += rang[x];
            head[x] = y;

            if (DSU_tin[DSU_Sdom[y]] < DSU_tin[DSU_Sdom[x]]) {
                DSU_Sdom[x] = DSU_Sdom[y];
            }
        }
        else {
            rang[x] += rang[y];
            head[y] = x;

            if (DSU_tin[DSU_Sdom[y]] < DSU_tin[DSU_Sdom[x]]) {
                DSU_Sdom[x] = DSU_Sdom[y];
            }
        }

        return true;
    }

    int Get_Sdom(int x) {
        int H = Find(x);
        return DSU_Sdom[H];
    }
};

vector<vector<int>> G;
vector<int> vis;

int Timer = 0;
vector<int> tin;

void dfs(int v) {
    vis[v] = true;
    tin[v] = Timer;
    Timer += 1;
    for (auto u : G[v]) {
        if (vis[u] == true) {
            continue;
        }
        dfs(u);
    }
}

vector<int> pred;

void dfs_pred(int v, int p) {
    vis[v] = true;
    pred[v] = p;
    for (auto u : G[v]) {
        if (vis[u] == true) {
            continue;
        }
        if (u == p) {
            continue;
        }
        dfs_pred(u, v);
    }
}

vector<int> Sdom;
vector<vector<int>> R_G;

void Build_Sdom(int n, int m, int s, DSU& dsu) {
    vector<pair<int, int>> reverse_dfs_path;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (tin[i] != 0) {
            reverse_dfs_path.push_back(make_pair(tin[i], i));
            ++k;
        }
    }

    sort(reverse_dfs_path.begin(), reverse_dfs_path.end());
    reverse(reverse_dfs_path.begin(), reverse_dfs_path.end());

    for (int i = 0; i < k - 1; i++) {
        int v = reverse_dfs_path[i].second;
        int t = reverse_dfs_path[i].first;

        dsu.Union(v, pred[v]);

        for (auto u : R_G[v]) {
            if (tin[u] > tin[v]) {
                Sdom[v] = min(Sdom[v], dsu.Get_Sdom(u));
                dsu.Union(v, u);
            }
        }
    }
}

vector<vector<int>> DFS_tree;

void Build_DFS_tree(int v) {
    vis[v] = true;
    for (auto u : G[v]) {
        if (vis[u] == false) {
            DFS_tree[v].push_back(u);
            Build_DFS_tree(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    set<pair<int, int>> E;

    int n, m, s;
    cin >> n >> m >> s;

    //--s;

    G.resize(n);
    R_G.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        //--u;
        //--v;

        if (v != s) {
            G[u].push_back(v);
            R_G[v].push_back(u);
        }

        E.insert({ u, v });
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }

    tin.resize(n);
    for (int i = 0; i < n; i++) {
        tin[i] = 0;
    }

    dfs(s);

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }

    pred.resize(n);
    for (int i = 0; i < n; i++) {
        pred[i] = 0;
    }

    dfs_pred(s, s);

    Sdom.resize(n);
    for (int i = 0; i < n; i++) {
        Sdom[i] = (int)1e9;
    }

    for (int u = 0; u < n; u++) {
        for (auto v : R_G[u]) {
            if (tin[v] < tin[u]) {
                if (Sdom[u] = (int)1e9) {
                    Sdom[u] = v;
                }
                else {
                    if (tin[Sdom[u]] > tin[v]) {
                        Sdom[u] = v;
                    }
                }
            }
        }
    }

    Sdom[s] = s;
    DSU dsu(n, Sdom, tin);
    Build_Sdom(n, m, s, dsu);

    DFS_tree.resize(n);

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }

    Build_DFS_tree(s);

    vector<int> Dom;
    Dom.resize(n);
    for (int i = 0; i < n; i++) {
        Dom[i] = -1;
    }
    Dom[s] = s;

    HLD hld(n);

    for (int u = 0; u < n; u++) {
        for (int v : DFS_tree[u]) {
            hld.Add_edge(u, v);
        }
    }

    hld.Decompose(s);

    for (int v = 0; v < n; v++) {
        hld.Update(v, Sdom[v]);
    }

    for (int v = 0; v < n; v++) {
        int vsdom = Sdom[v];

        if (vsdom != 1e9) {
            if (v == vsdom) {
                Dom[v] = vsdom;
            }
            else if (v == s) {
                Dom[v] = s;
            }
            else {
                int was = hld.Get_min(vsdom, vsdom);
                hld.Update(vsdom, 1e9);
                int u = hld.Get_min(v, vsdom);
                hld.Update(vsdom, was);

                if (Sdom[u] >= Sdom[v]) {
                    Dom[v] = Sdom[v];
                }
                else {
                    Dom[v] = Dom[u];
                }
            }
        }
    }

    print(Sdom);
    print(Dom);

    return 0;
}
