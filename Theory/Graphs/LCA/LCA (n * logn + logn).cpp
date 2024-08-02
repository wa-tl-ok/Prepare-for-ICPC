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

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    for (int i = LOGN - 1; i >= 0; --i) {
        if (depth[a] - (1 << i) >= depth[b]) {
            a = parent[a][i];
        }
    }

    if (a == b) {
        return a;
    }

    for (int i = LOGN - 1; i >= 0; --i) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }

    return parent[a][0];
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
        string op; int a, b;
        cin >> op >> a >> b;

        if (op == "ADD") {
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        else if (op == "GET") {
            vec.push_back(make_pair(a, b));
        }
    }

    dfs(1, 1, 0);

    for (int i = 0; i < (int)vec.size(); ++i) {
        cout << lca(vec[i].first, vec[i].second) << "\n";
    }

    return 0;
}
