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
vector<int> min_tin_in_node;
vector<int> vis;

int tin[1000000];
int tout[1000000];
int timer = 0;

void dfs(int v, int p) {
    vis[v] = true;
    tin[v] = (++timer);
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        dfs(u, v);
        min_tin_in_node[v] = min(min_tin_in_node[v], min_tin_in_node[u]);
    }
    tout[v] = (++timer);
    for (auto u : g[v]) {
        if (u != p) {
            min_tin_in_node[v] = min(min_tin_in_node[v], tin[u]);
        }
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

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    min_tin_in_node.resize(n);
    for (int i = 0; i < n; i++) {
        min_tin_in_node[i] = (int)1e9;
    }
    min_tin_in_node[0] = 0;

    dfs(0, 0);

    vector<int> answer;

    for (int u = 0; u < n; u++) {
        for (auto v : g[u]) {
            int a = u;
            int b = v;

            if (tin[a] > tin[b]) {
                swap(a, b);
            }

            if (min_tin_in_node[b] > tin[a]) {
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
