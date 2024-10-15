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

bool dfs(int u, vector<vector<int>>& g, vector<int>& vis) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (vis[v] == 0) {
            if (dfs(v, g, vis)) {
                return true;
            }
        }
        else if (vis[v] == 1) {
            return true;
        }
    }
    vis[u] = 2;
    return false;
}

bool Check(vector<vector<int>> g) {
    int n = g.size();
    vector<int> vis(n, 0);
    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            if (dfs(i, g, vis))
                return true;
        }
    }
    return false;
}

int Min_(vector<int>& a) {
    int mn = 1e9;
    for (auto p : a) {
        if (p != 0) {
            mn = min(mn, p);
        }
    }
    return mn;
}

int Max_(vector<int>& a) {
    int mx = -1e9;
    for (auto p : a) {
        if (p != 0) {
            mx = max(mx, p);
        }
    }
    return mx;
}

void Solve() {
    int H, W; cin >> H >> W;
    vector<vector<int>> M(H);
    for (int i = 0; i < H; i++) {
        M[i].resize(W);
    }
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> M[i][j];
        }
    }

    vector<int> visited(H * W + 1, false);
    vector<vector<int>> graph((H + 1) * (W + 1));

    for (int i = 0; i < H; i++) {
        map<int, vector<int>> Map;

        for (int j = 0; j < W; j++) {
            if (M[i][j] != 0) {
                Map[M[i][j]].push_back(j);
            }
        }

        int mn = Min_(M[i]);
        int mx = Max_(M[i]);

        for (int t = mn; t < mx; t++) {
            if (visited[t] == true) {
                cout << "No";
                return;
            }
            visited[t] = true;
        }

        int k = (i + 1) * (W + 1);
        for (auto& p : Map) {
            vector<int> a = p.second;
            for (auto v : a) {
                graph[k].push_back(v);
                graph[v].push_back(k + 1);
            }
            ++k;
        }
    }
    
    if (Check(graph) == true) {
        cout << "No";
        return;
    }

    cout << "Yes";
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
