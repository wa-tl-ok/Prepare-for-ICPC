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
vector<bool> vis;

void dfs(int u) {
    vis[u] = true;
    for (auto v : G[u]) {
        if (vis[v] != true) {
            dfs(v);
        }
    }
}

void Solve() {
    int n; cin >> n;
    int m; cin >> m;

    G.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int ans = 0;

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        if (vis[i] == false) {
            ++ans;
            dfs(i);
        }
    }

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
