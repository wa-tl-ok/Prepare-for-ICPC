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

vector<int> top_sort;
vector<int> SCC;
vector<int> vis;
vector<int> g[400010]; // 4 * max(n) + smth
vector<int> r_g[400010]; // 4 * max(n) + smth

void dfs(int v) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (vis[u] == true) {
            continue;
        }
        dfs(u);
    }
    top_sort.push_back(v);
}

int color = -1;

void Go(int v) {
    SCC[v] = color;
    for (auto u : r_g[v]) {
        if (SCC[u] == -1) {
            Go(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;

    vector<pair<int, int>> edges;

    function<void(int, int)> add = [&](int u, int v) {
        edges.push_back({ u, v });

        g[u].push_back(v);
        r_g[v].push_back(u);
    };

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v; 
        --u; --v;

        // add(u) if +
        // add(u + 2 * n) if -
    }

    vis.resize(4 * n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    for (int u = 0; u < 4 * n; u++) {
        if (vis[u] == false) {
            dfs(u);
        }
    }

    reverse(top_sort.begin(), top_sort.end());

    SCC.resize(4 * n);
    for (int i = 0; i < 4 * n; i++) {
        SCC[i] = -1;
    }

    for (int i = 0; i < 4 * n; i++) {
        if (SCC[top_sort[i]] == -1) {
            ++color;
            Go(top_sort[i]);
            ++color;
            Go(top_sort[i] + 2 * n);
        }
    }

    for (int u = 0; u < 2 * n; u++) {
        if (SCC[u] == SCC[u + 2 * n]) {
            cout << "NO";
            return 0;
        }
    }

    vector<vector<int>> G(color + 1);

    for (auto p : edges) {
        int u = p.first;
        int v = p.second;
        if (SCC[u] != SCC[v]) {
            G[SCC[u]].push_back(SCC[v]);
        }
    }

    map<int, vector<int>> Nodes_in_Comp;
    for (int i = 0; i < 4 * n; i++) {
        Nodes_in_Comp[SCC[i]].push_back(i);
    }

    int Components = color + 1;

    vector<int> vis_cond(Components, 0);
    vector<int> top_sort_cond;

    function<void(int)> dfs_cond = [&](int v) {
        vis_cond[v] = true;
        for (auto u : G[v]) {
            if (vis_cond[u] == true) {
                continue;
            }
            dfs_cond(u);
        }
        top_sort_cond.push_back(v);
    };

    for (int u = 0; u < Components; u++) {
        if (vis_cond[u] == false) {
            dfs_cond(u);
        }
    }

    vector<int> VIS(Components, false);

    for (int i = 0; i < Components; i++) {
        int u = top_sort_cond[i];
        int v = -1;
        if (u % 2 == 0) {
            v = u + 1;
        }
        else {
            v = u - 1;
        }
        if (VIS[v] == false) {
            VIS[u] = true;
        }
        else {
            VIS[u] = true;
            for (auto w : Nodes_in_Comp[u]) {
                if (w < 2 * n) {
                    cout << w + 1 << ' ';
                }
            }
        }
    }

    return 0;
}
