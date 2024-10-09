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

int ans = 0;

vector<vector<int>> G;
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    ++ans;

    if (ans > 1000000) {
        cout << 1000000;
        exit(0);
    }
    
    for (auto v : G[u]) {
        if (vis[v] == false) {
            dfs(v);
        }
    }

    vis[u] = false;
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

    dfs(0);

    cout << ans;
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
