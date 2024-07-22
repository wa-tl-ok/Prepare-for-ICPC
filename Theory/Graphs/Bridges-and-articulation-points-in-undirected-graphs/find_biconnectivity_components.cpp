#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
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

vector<vector<int>> g;
vector<int> min_tin_in_node;
vector<int> vis;

vector<int> buf = { };
int counter = 0;
map<int, vector<int>> C;

int tin[1000000];
int tout[1000000];
int timer = 0;

void dfs(int v, int p) {
    vis[v] = true;
    tin[v] = (++timer);
    buf.push_back(v);
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        dfs(u, v);
        min_tin_in_node[v] = min(min_tin_in_node[v], min_tin_in_node[u]);
    }
    tout[v] = (++timer);
    for (auto u : g[v]) {
        if (u != p) {
            min_tin_in_node[v] = min(min_tin_in_node[v], tin[u]);
        }
    }
    if (min_tin_in_node[v] > tin[p]) {
        while (buf[buf.size() - 1] != p) {
            C[counter].push_back(buf[buf.size() - 1]);
            buf.pop_back();
        }
        counter += 1;
    }
    if (v == 0) {
        C[counter] = {};
        for (auto b : buf) {
            C[counter].push_back(b);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;

    g.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u -= 1;
        v -= 1;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    min_tin_in_node.resize(n);
    for (int i = 0; i < n; i++) {
        min_tin_in_node[i] = (int)1e9;
    }
    min_tin_in_node[0] = 0;

    dfs(0, 0);

    for (auto [key, vec] : C) {
        cout << key << " : ";
        for (auto q : vec) {
            cout << q << ' ';
        }
        cout << endl;
    }

    return 0;
}
