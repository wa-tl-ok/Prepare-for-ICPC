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
vector<int> vis;
vector<int> height;
vector<int> min_height_in_node;

void DFS(int v, int p) {
    if (v == 0) {
        for (int i = 0; i < (int)g.size(); i++) {
            vis[i] = false;
        }
    }
    vis[v] = true;
    int mn = (int)1e9;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        DFS(u, v);
        min_height_in_node[v] = min(min_height_in_node[v], min_height_in_node[u]);
    }
    for (auto u : g[v]) {
        if (u != p) {
            min_height_in_node[v] = min(min_height_in_node[v], height[u]);
        }
    }
}

void dfs(int v, int p, int h) {
    vis[v] = true;
    height[v] = h;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        dfs(u, p, h + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m; cin >> n >> m;
    unordered_map<long long, int> ind;

    g.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u -= 1;
        v -= 1;
        g[u].push_back(v);
        g[v].push_back(u);

        if (u > v) {
            swap(u, v);
        }
        ind[u * 1000000 + v] = i + 1;
    }

    height.resize(n);
    for (int i = 0; i < n; i++) {
        height[i] = 0;
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    min_height_in_node.resize(n);
    for (int i = 0; i < n; i++) {
        min_height_in_node[i] = (int)1e9;
    }

    dfs(0, 0, 0);

    DFS(0, 0);

    vector<int> answer;

    for (int u = 0; u < n; u++) {
        for (auto v : g[u]) {
            int a = u;
            int b = v;

            if (height[a] > height[b]) {
                swap(a, b);
            }

            if (min_height_in_node[b] > height[a]) {
                if (a > b) {
                    swap(a, b);
                }

                if (ind[a * 1000000 + b] != 0) {
                    answer.push_back(ind[a * 1000000 + b]);
                    ind[a * 1000000 + b] = 0;
                }
            }
        }
    }

    sort(answer.begin(), answer.end());

    cout << answer.size() << endl;

    for (auto q : answer) {
        cout << q << ' ';
    }

    return 0;
}
