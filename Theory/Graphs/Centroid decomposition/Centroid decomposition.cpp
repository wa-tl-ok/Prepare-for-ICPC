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

vector<set<int>> graph;
vector<int> tree;
vector<int> parent;
int cnt;

int find_centroid(int u, int p) {
    for (auto v : graph[u]) {
        if (v != p) {
            if (tree[v] > cnt) {
                return find_centroid(v, u);
            }
        }
    }
    return u;
}

void dfs_decompose(int u, int p) {
    tree[u] = 1;
    cnt += 1;

    for (auto v : graph[u]) {
        if (v != p) {
            dfs_decompose(v, u);
            tree[u] += tree[v];
        }
    }
}

void decompose(int u, int p = -1) {
    cnt = 0;
    dfs_decompose(u, p);
    cnt /= 2;

    int center = find_centroid(u, p);
    parent[center] = p;

    for (auto v : graph[center]) {
        if (v != p) {
            graph[v].erase(center);
            decompose(v, center);
        }
    }

    graph[center].clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q; cin >> n >> q;

    graph.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    tree.resize(n);
    for (int i = 0; i < n; i++) {
        tree[i] = 0;
    }
    parent.resize(n);
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
    decompose(0);

    while (q > 0) {
        int type, v; cin >> type >> v;
        --v;

        if (type == 1) {
            int u = v;

            while (u != -1) {
                u = parent[u];
            }
        }
        else {
            int u = v;
            int answer = 1e9;

            while (u != -1) {
                u = parent[u];
            }

            cout << answer << endl;
        }

        --q;
    }

    return 0;
}
