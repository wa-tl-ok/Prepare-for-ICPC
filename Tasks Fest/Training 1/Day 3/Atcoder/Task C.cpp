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

vector<vector<int>> G;
vector<int> vis;

void dfs(int u, int p) {
    vis[u] = true;
    for (auto v : G[u]) {
        if (v != p && vis[v] == false) {
            dfs(v, u);
        }
    }
}

void Solve() {
    int n, m; cin >> n >> m;
    G.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    int C = 0;

    for (int i = 0; i < n; i++) {
        if (vis[i] == false) {
            dfs(i, i);
            ++C;
        }
    }

    int need = n - C;

    cout << max(0, m - need);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
