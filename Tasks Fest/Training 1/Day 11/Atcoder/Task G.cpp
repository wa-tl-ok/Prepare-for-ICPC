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
int c = 0;

void dfs(int u) {
    vis[u] = c;
    for (auto v : G[u]) {
        if (vis[v] == -1) {
            dfs(v);
        }
    }
}

void Solve() {
    int n, m; 
    cin >> n >> m;

    map<int, pair<int, int>> E;
    map<int, bool> V;

    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        E[i] = make_pair(u, v);
        V[i] = true;
    }

    int k; cin >> k;
    for (int i = 0; i < k; i++) {
        int id; cin >> id;
        V[id] = false;
    }

    G.resize(n);
    for (int i = 1; i <= m; i++) {
        if (V[i] == true) {
            int u = E[i].first;
            int v = E[i].second;

            G[u].push_back(v);
            G[v].push_back(u);
        }
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = -1;
    }

    for (int u = 0; u < n; u++) {
        if (vis[u] == -1) {
            dfs(u);
            ++c;
        }
    }

    map<int, int> st;
    for (int i = 1; i <= m; i++) {
        if (V[i] == false) {
            int u = E[i].first;
            int v = E[i].second;

            int cu = vis[u];
            int cv = vis[v];

            st[cu] += 1;
            st[cv] += 1;
        }
    }

    int K = 0;
    for (auto p : st) {
        if (p.second % 2 == 1) {
            K += 1;
        }
    }

    if (K == 0 || K == 2) {
        cout << "Yes";
    }
    else {
        cout << "No";
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
