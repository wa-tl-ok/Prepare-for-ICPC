//https://contest.yandex.ru/contest/62775/problems/D/

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
#include <random>

using namespace std;

vector<int> top_sort;
vector<int> SCC;
vector<int> vis;
vector<vector<int>> g;
vector<vector<int>> r_g;

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

    set<pair<int, int>> edges;

    g.resize(n);
    r_g.resize(n);

    vector<int> in(n, 0);
    vector<int> out(n, 0);

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        if (u != v) {
            edges.insert({ u, v });

            g[u].push_back(v);
            r_g[v].push_back(u);

            ++out[u];
            ++in[v];
        }
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    for (int u = 0; u < n; u++) {
        if (vis[u] == false) {
            dfs(u);
        }
    }

    reverse(top_sort.begin(), top_sort.end());

    SCC.resize(n);
    for (int i = 0; i < n; i++) {
        SCC[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (SCC[top_sort[i]] == -1) {
            ++color;
            Go(top_sort[i]);
        }
    }

    vector<set<int>> G(color + 1);

    for (auto p : edges) {
        int u = p.first;
        int v = p.second;
        if (SCC[u] != SCC[v]) {
            G[SCC[u]].insert(SCC[v]);
        }
    }

    map<int, int> weight_component;

    for (int i = 0; i < n; i++) {
        ++weight_component[SCC[i]];
    }

    int Components = color + 1;

    // Solving task start //

    vector<int> vis_cond(Components, 0);
    vector<int> top_sort_cond;
    vector<int> in_cond(Components, 0);
    vector<int> out_cond(Components, 0);

    for (int u = 0; u < Components; u++) {
        for (auto v : G[u]) {
            ++in_cond[v];
            ++out_cond[u];
        }
    }

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

    vis_cond.resize(Components);
    for (int i = 0; i < Components; i++) {
        vis_cond[i] = false;
    }

    for (int u = 0; u < Components; u++) {
        if (vis_cond[u] == false) {
            dfs_cond(u);
        }
    }

    reverse(top_sort_cond.begin(), top_sort_cond.end());

    int now = Components - 1;
    int F = -1;
    int S = -1;

    for (int i = 0; i < Components - 1; i++) {
        int u = top_sort_cond[i];
        int v = top_sort_cond[i + 1];
        if (G[u].find(v) == G[u].end()) {
            F = u;
            S = v;
        }
    }

    if (F == -1) {
        cout << 0;
    }
    else {
        int v1 = -1;
        int v2 = -1;
        for (int u = 0; u < n; u++) {
            if (SCC[u] == F) {
                v1 = u + 1;
            }
            if (SCC[u] == S) {
                v2 = u + 1;
            }
        }
        cout << v1 << ' ' << v2;
    }

    // Solving task end //

    return 0;
}
