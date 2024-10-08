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
        if (vis[v] == false) {
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

    if (m != n - 1) {
        cout << "No";
        return;
    }

    int one = 0;
    int two = 0;

    for (int i = 0; i < n; i++) {
        if (G[i].size() == 1) {
            ++one;
        }
        else if (G[i].size() == 2) {
            ++two;
        }
    }

    if (one == 2 && two == n - 2) {
        vis.resize(n);
        for (int i = 0; i < n; i++) {
            vis[i] = false;
        }

        dfs(0);

        for (int i = 0; i < n; i++) {
            if (vis[i] == false) {
                cout << "No";
                return;
            }
        }

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
