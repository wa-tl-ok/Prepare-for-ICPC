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

vector<int> answer;

vector<vector<int>> g;
vector<int> vis;
vector<int> height;
vector<int> min_height_in_node;

void Erase_dfs(int v, int p) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        if (u == 0) {
            continue;
        }
        Erase_dfs(u, v);
    }
}

void DFS(int v, int p) {
    if (v == 0) {
        for (int i = 0; i < (int)g.size(); i++) {
            vis[i] = false;
        }
    }
    vis[v] = true;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        DFS(u, v);
        if (v != 0 && min_height_in_node[u] >= height[v]) {
            answer.push_back(v + 1);
        }
    }
    if (v == 0) {
        for (int i = 0; i < (int)g.size(); i++) {
            vis[i] = false;
        }
        Erase_dfs(1, 1);
        for (int i = 1; i < (int)g.size(); i++) {
            if (vis[i] == false) {
                answer.push_back(1);
                break;
            }
        }
    }
}

void dfs(int v, int p) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (u == p) {
            continue;
        }
        if (vis[u] == true) {
            continue;
        }
        dfs(u, v);
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

    g.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u -= 1;
        v -= 1;
        g[u].push_back(v);
        g[v].push_back(u);
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
    min_height_in_node[0] = 0;

    dfs(0, 0, 0); 
    
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }
    
    dfs(0, 0); 
    
    DFS(0, 0);

    set<int> uniq(answer.begin(), answer.end());
    vector<int> answer(uniq.begin(), uniq.end());

    cout << answer.size() << endl;
    for (auto q : answer) {
        cout << q << "\n";
    }

    return 0;
}
