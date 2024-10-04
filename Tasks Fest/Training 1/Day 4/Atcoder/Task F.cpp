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

#define int long long

vector<vector<pair<int, int>>> G;
vector<int> dist;

vector<int> Color;
int now_color = -1;

map<int, bool> Good;

void dfs(int u) {
    Color[u] = now_color;
    for (auto p : G[u]) {
        if (Color[p.first] == -1) {
            dist[p.first] = dist[u] + p.second;
            dfs(p.first);
        }
        else {
            if (dist[p.first] != dist[u] + p.second) {
                Good[now_color] = false;
            }
        }
    }
}

void Solve() {
    int n, m, q; 
    cin >> n >> m >> q;

    G.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        int c; cin >> c;
        G[u].push_back({ v, c });
        G[v].push_back({ u, -c });
    }

    Color.resize(n);
    for (int i = 0; i < n; i++) {
        Color[i] = -1;
    }

    dist.resize(n);
    for (int i = 0; i < n; i++) {
        dist[i] = 1e18;
    }

    for (int i = 0; i < n; i++) {
        if (Color[i] == -1) {
            Good[++now_color] = true;
            dist[i] = 0;
            dfs(i);
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        if (Color[u] != Color[v]) {
            cout << "nan" << '\n';
        }
        else if (Good[Color[u]] == false) {
            cout << "inf" << '\n';
        }
        else {
            cout << dist[v] - dist[u] << '\n';
        }
    }
}

signed main() {
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
