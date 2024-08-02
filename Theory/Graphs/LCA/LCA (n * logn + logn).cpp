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
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cassert>

using namespace std;

const int MAXN = 2e6 + 5;
const int LOGN = 23;

vector<int> graph[MAXN];
int parent[MAXN][LOGN];

int depth[MAXN];
int n;

void dfs(int v, int p, int d) {
    depth[v] = d;
    parent[v][0] = p;

    for (int i = 1; i < LOGN; ++i) {
        parent[v][i] = parent[parent[v][i - 1]][i - 1];
    }

    for (int u : graph[v]) {
        if (u != p) {
            dfs(u, v, d + 1);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (int i = LOGN - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) {
        return u;
    }

    for (int i = LOGN - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);

    cin >> n;
    vector<pair<int, int>> vec;

    for (int i = 1; i <= n; ++i) {
        string op; int u, v;
        cin >> op >> u >> v;

        --u;
        --v;

        if (op == "ADD") {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        else if (op == "GET") {
            vec.push_back(make_pair(u, v));
        }
    }

    dfs(0, 0, 0);

    for (int i = 0; i < (int)vec.size(); ++i) {
        cout << lca(vec[i].first, vec[i].second) + 1 << "\n";
    }

    return 0;
}
