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
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cassert>

using namespace std;

class Sparse_table_min {
private:
    int N, K;
    vector<vector<int>> Stable;
public:
    Sparse_table_min(const vector<int>& vec) {
        this->N = (int)(vec.size());
        this->K = log2(N) + 2;

        Stable.resize(N + 1);

        for (int i = 0; i < N; i++) {
            Stable[i].resize(K + 1);
            Stable[i][0] = vec[i];
        }

        for (int j = 1; (1 << j) <= N; j++) {
            for (int i = 0; i + (1 << j) - 1 < N; i++) {
                Stable[i][j] = min(Stable[i][j - 1], Stable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r) {
        int mn = 1e9;
        int sz = r - l + 1;

        for (int k = K; k >= 0; k--) {
            if (sz >= (1 << k)) {
                mn = min(mn, Stable[l][k]);
                sz -= 1 << k;

                l += 1 << k;
            }
        }

        return mn;
    }
};

vector<vector<int>> graph;
vector<int> vis;
vector<int> nodes;

void dfs(int u, int p) {
    vis[u] = true;

    nodes.push_back(u);

    for (int& v : graph[u]) {
        if (vis[v] == false) {
            dfs(v, u);
            nodes.push_back(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);

    int n; cin >> n;

    graph.resize(n);

    vector<pair<int, int>> queries;

    for (int i = 0; i < n; ++i) {
        string op; int u, v;
        cin >> op >> u >> v;

        --u;
        --v;

        if (op == "ADD") {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        else if (op == "GET") {
            queries.push_back(make_pair(u, v));
        }
    }

    vis.resize(n);
    for (int i = 0; i < n; i++) {
        vis[i] = false;
    }

    dfs(0, 0);

    vector<int> last_ind(n, -1);
    for (int i = 0; i < (int)nodes.size(); i++) {
        last_ind[nodes[i]] = i;
    }

    Sparse_table_min ST(nodes);

    for (const auto& query : queries) {
        int u = query.first;
        int v = query.second;

        int l = last_ind[u];
        int r = last_ind[v];

        if (l > r) {
            swap(l, r);
        }

        cout << ST.query(l, r) + 1 << "\n";
    }

    return 0;
}
