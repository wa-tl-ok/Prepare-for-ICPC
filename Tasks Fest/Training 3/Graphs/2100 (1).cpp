//https://codeforces.com/contest/1811/problem/F

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
#include <iomanip>

using namespace std;

#define int long long

void Solve() {
    int n, m; 
    cin >> n >> m;
    int k = sqrt(n);

    vector<bool> vis(n);
    for (int j = 0; j < n; j++) {
        vis[j] = false;
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (k * k != n) {
        cout << "NO\n";
        return;
    }

    if (k * k + k != m) {
        cout << "NO\n";
        return;
    }

    int c2 = 0;
    int c4 = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].size() == 2) {
            ++c2;
        }
        if (g[i].size() == 4) {
            ++c4;
        }
    }

    if (c2 + c4 != n) {
        cout << "NO\n";
        return;
    }

    if (c4 != k) {
        cout << "NO\n";
        return;
    }

    function<void(int)> dfs1 = [&](int u) {
        vis[u] = true;
        for (auto v : g[u]) {
            if (vis[v] == false && g[v].size() == 4) {
                dfs1(v);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (vis[i] == false && g[i].size() == 4) {
            dfs1(i);
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (g[i].size() == 4) {
            if (vis[i] == false) {
                cout << "NO\n";
                return;
            }
        }
    }

    int now = 0;
    int node = 0;
    bool f = true;
    function<void(int)> dfs2 = [&](int u) {
        ++now;
        vis[u] = true;
        for (auto v : g[u]) {
            if (vis[v] == false) {
                dfs2(v);
            }
            else {
                if (node != v && g[v].size() == 4) {
                    f = false;
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        if (g[i].size() == 4) {
            int v = -1;

            for (auto u : g[i]) {
                if (vis[u] == false) {
                    v = u;
                    break;
                }
            }

            if (v == -1) {
                cout << "NO\n";
                return;
            }

            now = 1;
            node = i;
            f = true;

            dfs2(v);

            if (now != k) {
                cout << "NO\n";
                return;
            }

            if (f == false) {
                cout << "NO\n";
                return;
            }
        }
    }

    cout << "YES\n";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
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
