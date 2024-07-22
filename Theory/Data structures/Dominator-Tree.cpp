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

struct DSU {
    vector<int> head;
    vector<int> rang;
    vector<int> DSU_Sdom;
    vector<int> DSU_tin;

    DSU(int n, vector<int> &Sdom, vector<int> &tin) {
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

void Build_Sdom(int n, int m, int s, DSU & dsu) {
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
        if (vis[u] == true) {
            continue;
        }
        DFS_tree[v].push_back(u);
        DFS_tree[u].push_back(v);
        dfs(u);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;

    --s;

    G.resize(n);
    R_G.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        --u;
        --v;

        if (v != s) {
            G[u].push_back(v);
            R_G[v].push_back(u);
        }
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

    print(Sdom);

    return 0;
}

/*
9 13 1
1 2
1 7
7 8
8 9
9 7
9 6
2 3
2 4
5 3
4 5
4 6
6 5
2 5

4 3 1
2 3
3 4
4 2
*/
