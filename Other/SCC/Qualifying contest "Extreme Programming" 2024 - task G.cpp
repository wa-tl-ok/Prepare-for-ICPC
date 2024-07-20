#include <iostream> 
#include <iomanip> 
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
#include <random> 

using namespace std;

vector<int> top_sort;
vector<int> SCC;
vector<int> vis;
vector<vector<int>> g;
vector<vector<int>> r_g;

void dfs(int v) {
    vis[v] = true;
    for (auto u : g[v]) {
        if (vis[u] == true) {
            continue;
        }
        dfs(u);
    }
    top_sort.push_back(v);
}

int color = -1;

void Go(int v) {
    SCC[v] = color;
    for (auto u : r_g[v]) {
        if (SCC[u] == -1) {
            Go(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    struct Trio {
        int x;
        int y;
        int r;
    };

    int n; cin >> n;
    vector<Trio> nodes;

    for (int i = 0; i < n; i++) {
        int x, y, r; 
        cin >> x >> y >> r;

        Trio t;

        t.x = x;
        t.y = y;
        t.r = r;

        nodes.push_back(t);
    }

    set<pair<int, int>> edges;

    g.resize(n);
    r_g.resize(n);

    int m = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x1 = nodes[i].x;
            int y1 = nodes[i].y;
            int r1 = nodes[i].r;

            int x2 = nodes[j].x;
            int y2 = nodes[j].y;
            int r2 = nodes[j].r;

            if (r1 * r1 >= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) {
                g[i].push_back(j);
                r_g[j].push_back(i);
                ++m;

                edges.insert({ i, j });
            }
                
            if (r2 * r2 >= (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) {
                g[j].push_back(i);
                r_g[i].push_back(j);
                ++m;

                edges.insert({ j, i });
            }
        }
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    for (int u = 0; u < n; u++) {
        if (vis[u] == false) {
            dfs(u);
        }
    }

    reverse(top_sort.begin(), top_sort.end());

    SCC.resize(n);
    for (int i = 0; i < n; i++) {
        SCC[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (SCC[top_sort[i]] == -1) {
            ++color;
            Go(top_sort[i]);
        }
    }

    vector<set<int>> G(color + 1);

    for (auto p : edges) {
        int u = p.first;
        int v = p.second;
        if (SCC[u] != SCC[v]) {
            G[SCC[u]].insert(SCC[v]);
        }
    }

    int Components = color + 1;

    vector<int> vis_cond(Components, 0);
    vector<int> top_sort_cond;
    vector<int> in_cond(Components, 0);
    vector<int> out_cond(Components, 0);

    for (int u = 0; u < Components; u++) {
        for (auto v : G[u]) {
            ++in_cond[v];
            ++out_cond[u];
        }
    }

    function<void(int)> dfs_cond = [&](int v) {
        vis_cond[v] = true;
        for (auto u : G[v]) {
            if (vis_cond[u] == true) {
                continue;
            }
            dfs_cond(u);
        }
        top_sort_cond.push_back(v);
    };

    function<void(int)> DFS = [&](int v) {
        vis_cond[v] = true;
        for (auto u : G[v]) {
            if (vis_cond[u] == true) {
                continue;
            }
            DFS(u);
        }
    };

    vis_cond.resize(Components);
    for (int i = 0; i < Components; i++) {
        vis_cond[i] = false;
    }

    for (int u = 0; u < Components; u++) {
        if (vis_cond[u] == false) {
            dfs_cond(u);
        }
    }

    reverse(top_sort_cond.begin(), top_sort_cond.end());

    vis_cond.resize(Components);
    for (int i = 0; i < Components; i++) {
        vis_cond[i] = false;
    }

    int ans = 0;

    for (auto p : top_sort_cond) {
        if (vis_cond[p] == false) {
            DFS(p);
            ans += 1;
        }
    }

    cout << ans;

    return 0;
}
