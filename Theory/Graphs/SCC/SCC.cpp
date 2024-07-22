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

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        if (u != v) {
            edges.insert({ u, v });

            g[u].push_back(v);
            r_g[v].push_back(u);
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

    return 0;
}
