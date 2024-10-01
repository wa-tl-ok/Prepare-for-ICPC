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

set<int> ans;

void dfs(int v) {
    vis[v] = true;
    for (auto u : G[v]) {
        if (vis[u] == false) {
            dfs(u);
        }
    }

    if (G[v].size() == 0) {
        ans.insert(v + 1);
    }
}

void Solve() {
    int n; cin >> n;

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    G.resize(n);

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        if (h[u] > h[v]) {
            G[u].push_back(v);
        }

        if (h[u] < h[v]) {
            G[v].push_back(u);
        }
    }

    dfs(0);

    for (auto r : ans) {
        cout << r << ' ';
    }
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
